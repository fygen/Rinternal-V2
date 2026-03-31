import os
import re

search_path = "./lib"
output_file = "./lib/HELPER/GeneratedDispatcher.cpp"

# --- CONFIGURATION ---
EXCLUDE_FILES = ["InternalTest.h"] 
EXCLUDE_METHODS = ["getInstance", "beginAll", "resetFactory", "debugInternalState", "dispatchCommand", "setup", "loop", "handleExecute", "commandParseAndExecute","copyto"]
# ------------------------------

method_pattern = r"(\w+[\s\*&]+)(\w+)\s*\((.*?)\);"
commands = []

# 1. SCANNING PHASE
for root, dirs, files in os.walk(search_path):
    for file in files:
        if file.endswith(".h") and file not in EXCLUDE_FILES:
            module_name = file.split('.')[0]
            with open(os.path.join(root, file), "r", encoding="utf-8") as f:
                content = f.read()
                
                if "public:" in content:
                    public_section = content.split("public:")[1].split("private:")[0].split("protected:")[0]
                    matches = re.findall(method_pattern, public_section)
                    
                    for ret_type, method_name, params_raw in matches:
                        ret_type = ret_type.strip()
                        if method_name in EXCLUDE_METHODS or method_name == module_name or "virtual" in ret_type:
                            continue

                        param_list = []
                        if params_raw.strip():
                            # Extract types for dispatching, but keep raw for display
                            for p in params_raw.split(','):
                                p = p.strip()
                                p_parts = p.split(' ')
                                p_type = " ".join(p_parts[:-1]) if len(p_parts) > 1 else p_parts[0]
                                param_list.append(p_type.strip())

                        commands.append({
                            'module': module_name,
                            'name': method_name,
                            'ret': ret_type,
                            'params': param_list
                        })

# 2. GENERATION PHASE
with open(output_file, "w", encoding="utf-8") as f:
    f.write('// AUTO-GENERATED FILE - DO NOT EDIT\n')
    f.write('#include <Arduino.h>\n#include "SYSTEM.h"\n#include "HELPER.h"\n')
    
    unique_modules = sorted(list(set(cmd['module'] for cmd in commands)))
    for mod in unique_modules:
        f.write(f'#include "{mod}.h"\n')
    
    # --- dispatchCommand Implementation ---
    f.write('\nString HELPER::dispatchCommand(String mod, String cmd, std::vector<String> args) {\n')
    f.write('    String logMsg = "[CMD] " + mod + " " + cmd;\n')
    f.write('    for(const auto& a : args) logMsg += " \'" + a + "\'";\n')
    f.write('    sys.server->logger(logMsg);\n\n')
    
    # Special case for HELPER methods that might not be in the commands list
    f.write('    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getHelp")) return getHelp();\n')
    f.write('    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getCommandsJSON")) return getCommandsJSON();\n')

    for cmd in commands:
        num_params = len(cmd['params'])
        f.write(f'    if (mod.equalsIgnoreCase("{cmd["module"]}") && cmd.equalsIgnoreCase("{cmd["name"]}")) {{\n')
        f.write(f'        if (args.size() < {num_params}) {{\n')
        f.write(f'            String err = "Error: {num_params} params required!";\n')
        f.write('            sys.server->logger("[RES] " + err);\n')
        f.write('            return err;\n')
        f.write('        }\n')
        
        call_args = []
        for i, p_type in enumerate(cmd['params']):
            pt = p_type.lower()
            is_last = (i == num_params - 1)
            
            # Greedy join for the last parameter if it's a string/char*
            if is_last and ("string" in pt or "char*" in pt or "char *" in pt):
                f.write(f'        String joinedArgs{i} = "";\n')
                f.write(f'        for(size_t j = {i}; j < args.size(); j++) {{\n')
                f.write(f'            joinedArgs{i} += args[j] + (j < args.size() - 1 ? " " : "");\n')
                f.write(f'        }}\n')
                
                if "char" in pt:
                    call_args.append(f"joinedArgs{i}.c_str()")
                else:
                    call_args.append(f"joinedArgs{i}")
            else:
                if any(x in pt for x in ["int", "long", "short"]):
                    call_args.append(f"args[{i}].toInt()")
                elif any(x in pt for x in ["float", "double"]):
                    call_args.append(f"args[{i}].toFloat()")
                elif "bool" in pt:
                    call_args.append(f"(args[{i}].equalsIgnoreCase(\"true\") || args[{i}] == \"1\")")
                elif "char" in pt:
                    call_args.append(f"args[{i}].c_str()")
                else:
                    call_args.append(f"args[{i}]")
        
        args_str = ", ".join(call_args)
        if cmd['module'].lower() == "system":
            instance = "sys."
        else:
            instance = f"sys.{cmd['module'].lower()}->"
        
        ret = cmd['ret'].lower()
        if "void" in ret:
            f.write(f'        {instance}{cmd["name"]}({args_str});\n')
            f.write('        sys.server->logger("[RES] OK");\n')
            f.write('        return "OK";\n')
        else:
            f.write(f'        String res = String({instance}{cmd["name"]}({args_str}));\n')
            f.write('        sys.server->logger("[RES] " + res);\n')
            f.write('        return res;\n')
        f.write('    }\n')
    
    f.write('\n    String finalErr = "Error: Command not found!";\n')
    f.write('    sys.server->logger("[RES] " + finalErr);\n')
    f.write('    return finalErr;\n}\n')

    # --- getCommandsJSON Implementation ---
    f.write('\nString HELPER::getCommandsJSON() {\n')
    f.write('    String j = "[";\n')
    for i, cmd in enumerate(commands):
        f.write('    j += "{";\n')
        f.write(f'    j += "\\"module\\": \\"{cmd["module"]}\\", ";\n')
        f.write(f'    j += "\\"name\\": \\"{cmd["name"]}\\", ";\n')
        f.write('    j += "\\"params\\": [";\n')
        for pi, p_type in enumerate(cmd['params']):
            f.write(f'    j += "\\"{p_type}\\"";\n')
            if pi < len(cmd['params']) - 1:
                f.write('    j += ", ";\n')
        f.write('    j += "]";\n')
        f.write('    j += "}";\n')
        if i < len(commands) - 1:
            f.write('    j += ", ";\n')
    f.write('    j += "]";\n')
    f.write('    return j;\n')
    f.write('}\n')

    # --- getHelp Implementation (THE CONTROL PANEL) ---
    f.write('\nString HELPER::getHelp() {\n')
    f.write('    String h = "<div style=\'text-align:left; font-family:sans-serif; background:#1e1e1e; padding:15px; border-radius:8px; color:#ddd; border:1px solid #333;\'>";\n')
    f.write('    h += "<h2 style=\'color:#4CAF50; margin-top:0;\'>Remote Control Panel</h2>";\n')
    
    current_mod = ""
    for idx, cmd in enumerate(sorted(commands, key=lambda x: x['module'])):
        if current_mod != cmd['module']:
            current_mod = cmd['module']
            f.write(f'    h += "<h3 style=\'color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;\'>{current_mod}</h3>";\n')
        
        # Unique ID for the input fields of this specific command
        cmd_id = f"{cmd['module']}_{cmd['name']}_{idx}"
        
        f.write(f'    h += "<div style=\'margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;\'>";\n')
        f.write(f'    h += "<strong>{cmd["name"]}</strong><br>";\n')
        
        # Build the JS string for hx-vals
        js_val = f"js:{{val: '{cmd['module']} {cmd['name']}"
        
        for p_idx, p_type in enumerate(cmd['params']):
            input_id = f"input_{cmd_id}_{p_idx}"
            f.write(f'    h += "<input id=\'{input_id}\' placeholder=\'{p_type}\' style=\'width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;\'> ";\n')
            js_val += f" ' + document.getElementById('{input_id}').value + '"
        
        js_val += "'}"
        
        f.write(f'    h += "<button hx-post=\'/execute\' hx-vals=\\\"{js_val}\\\" hx-target=\'#terminal-res\' style=\'background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;\'>Run</button>";\n')
        f.write(f'    h += "</div>";\n')
        
    f.write('    h += "</div>";\n')
    f.write('    return h;\n')
    f.write('}\n')

print(f"Success! Generated {len(commands)} interactive commands.")