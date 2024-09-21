
set_languages("cxx23")

target("d3d12helper")
    if is_mode("release") then
        set_kind("static")
    else
        set_kind("shared")
    end 
    add_includedirs("include",{public=true})
    add_files("src/*.cpp")
    add_syslinks("d3d12", "dxgi", "d3dcompiler", "dxguid")