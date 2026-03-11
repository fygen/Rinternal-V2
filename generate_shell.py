import os
import re

search_path = "./lib"
output_file = "./lib/HELPER/GeneratedDispatcher.cpp"

# --- CONFIGURATION ---
EXCLUDE_FILES = ["SYSTEM.h", "InternalTest.h"] 
EXCLUDE_METHODS = ["resetFactory", "debugInternalState", "dispatchCommand", "setup", "loop"]
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
                    # Focus only on public methods
                    public_section = content.split("public:")[1].split("private:")[0].split("protected:")[0]
                    matches = re.findall(method_pattern, public_section)
                    
                    for ret_type, method_name, params_raw in matches:
                        ret_type = ret_type.strip()
                        
                        # Filter out constructors, excluded methods, and virtuals
                        if method_name in EXCLUDE_METHODS or method_name == module_name or "virtual" in ret_type:
                            continue

                        param_list = []
                        if params_raw.strip():
                            for p in params_raw.split(','):
                                p = p.strip()
                                # Extract just the type (e.g., "String message" -> "String")
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
    # Headers
    f.write('// AUTO-GENERATED FILE - DO NOT EDIT\n')
    f.write('#include <Arduino.h>\n#include "SYSTEM.h"\n#include "HELPER.h"\n')
    
    unique_modules = sorted(list(set(cmd['module'] for cmd in commands)))
    for mod in unique_modules:
        f.write(f'#include "{mod}.h"\n')
    
    # --- dispatchCommand Implementation ---
    f.write('\nString HELPER::dispatchCommand(String mod, String cmd, std::vector<String> args) {\n')
    
    for cmd in commands:
        num_params = len(cmd['params'])
        f.write(f'    if (mod.equalsIgnoreCase("{cmd["module"]}") && cmd.equalsIgnoreCase("{cmd["name"]}")) {{\n')
        f.write(f'        if (args.size() < {num_params}) return "Error: {num_params} params required!";\n')
        
# Argument parsing logic
        call_args = []
        for i, p_type in enumerate(cmd['params']):
            pt = p_type.lower()
            if "int" in pt or "long" in pt:
                call_args.append(f"args[{i}].toInt()")
            elif "float" in pt or "double" in pt:
                call_args.append(f"args[{i}].toFloat()")
            elif "bool" in pt:
                call_args.append(f"(args[{i}].equalsIgnoreCase(\"true\") || args[{i}] == \"1\")")
            elif "char" in pt: # <--- THIS IS THE KEY FIX
                # This covers const char*, char*, etc.
                call_args.append(f"args[{i}].c_str()")
            else:
                call_args.append(f"args[{i}]") # Defaults to String object
        
        args_str = ", ".join(call_args)
        # Note: assumes sys.[modulename] exists in lowercase in SYSTEM.h
        instance = f"sys.{cmd['module'].lower()}->"
        
        ret = cmd['ret'].lower()
        if "void" in ret:
            f.write(f'        {instance}{cmd["name"]}({args_str});\n        return "OK";\n')
        elif "bool" in ret:
            f.write(f'        return {instance}{cmd["name"]}({args_str}) ? "true" : "false";\n')
        else:
            f.write(f'        return String({instance}{cmd["name"]}({args_str}));\n')
            
        f.write('    }\n')
    
    f.write('\n    return "Error: Command not found!";\n}\n')

    # --- getHelp Implementation ---
    f.write('\nString HELPER::getHelp() {\n')
    f.write('    String h = "<div style=\'text-align:left; font-family:monospace; font-size:12px;\'>";\n')
    f.write('    h += "<b style=\'color:#00ff00\'>--- SYSTEM HELP ---</b><br>";\n')
    
    current_mod = ""
    for cmd in sorted(commands, key=lambda x: x['module']):
        if current_mod != cmd['module']:
            current_mod = cmd['module']
            f.write(f'    h += "<br><b style=\'color:#ffcc00\'>[{current_mod}]</b><br>";\n')
        
        params_display = ", ".join(cmd['params'])
        f.write(f'    h += " - {cmd["name"]}({params_display})<br>";\n')
        
    f.write('    h += "</div>";\n')
    f.write('    return h;\n')
    f.write('}\n')

print(f"Success! Generated {len(commands)} commands across {len(unique_modules)} modules.")