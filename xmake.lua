
set_languages("cxx23")

target("d3d12helper")
    set_kind("static")
    add_includedirs("include",{public=true})
    add_files("src/*.cpp")
    add_syslinks("d3d12", "dxgi", "d3dcompiler", "dxguid")
