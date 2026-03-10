import os
import re

search_path = "./lib"
output_file = "./src/GeneratedDispatcher.cpp"

# --- EXCLUDE YAPILANDIRMASI ---
EXCLUDE_FILES = ["SYSTEM.h", "InternalTest.h"] # Bu dosyalar tamamen taranmaz
EXCLUDE_METHODS = ["resetFactory", "debugInternalState"] # Bu isimdeki metodlar dahil edilmez
# ------------------------------

method_pattern = r"(\w+[\s\*&]+)(\w+)\s*\((.*?)\);"
commands = []

for root, dirs, files in os.walk(search_path):
    for file in files:
        # Dosya bazlı filtreleme
        if file.endswith(".h") and file not in EXCLUDE_FILES:
            module_name = file.split('.')[0]
            with open(os.path.join(root, file), "r", encoding="utf-8") as f:
                content = f.read()
                
                if "public:" in content:
                    public_section = content.split("public:")[1].split("private:")[0].split("protected:")[0]
                    matches = re.findall(method_pattern, public_section)
                    
                    for ret_type, method_name, params_raw in matches:
                        ret_type = ret_type.strip()
                        
                        # Metod bazlı filtreleme ve constructor kontrolü
                        if method_name in EXCLUDE_METHODS or method_name == module_name or "virtual" in ret_type:
                            continue

                        param_list = []
                        if params_raw.strip():
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

# Dispatcher yazma kısmı (Aynı kalıyor...)
with open(output_file, "w", encoding="utf-8") as f:
    f.write('#include <Arduino.h>\n#include "SYSTEM.h"\n')
    for mod in set(cmd['module'] for cmd in commands):
        f.write(f'#include "{mod}.h"\n')
    
    f.write('\nString dispatchCommand(String mod, String cmd, std::vector<String> args) {\n')
    
    for cmd in commands:
        # Argüman sayısı kontrolü ekleyelim (Güvenlik için)
        num_params = len(cmd['params'])
        f.write(f'    if (mod.equalsIgnoreCase("{cmd["module"]}") && cmd.equalsIgnoreCase("{cmd["name"]}")) {{\n')
        f.write(f'        if (args.size() < {num_params}) return "Hata: En az {num_params} parametre gerekli!";\n')
        
        call_args = []
        for i, p_type in enumerate(cmd['params']):
            p_type_lower = p_type.lower()
            if "int" in p_type_lower or "long" in p_type_lower:
                call_args.append(f"args[{i}].toInt()")
            elif "float" in p_type_lower or "double" in p_type_lower:
                call_args.append(f"args[{i}].toFloat()")
            elif "char" in p_type_lower:
                call_args.append(f"args[{i}].c_str()")
            else:
                call_args.append(f"args[{i}]")
        
        args_str = ", ".join(call_args)
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

print(f"Toplam {len(commands)} komut eklendi ({len(EXCLUDE_FILES)} dosya ve {len(EXCLUDE_METHODS)} metod hariç tutuldu).")