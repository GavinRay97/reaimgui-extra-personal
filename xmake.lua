-- Requires will try to use either system package manager, or third-party package manages (vcpkg, Conan, etc)
-- To automatically find and wire up library dependencies
add_rules("mode.debug", "mode.release")
add_requires("vcpkg::imgui 1.82", "boost-core", "boost-preprocessor", "boost-type-index")

-- 1. Set the current config: $ xmake config --plat=windows --mode=debug --arch=x64 --verbose --diagnosis --clean
-- 2. Then run the build:     $ xmake build --verbose --diagnosis
-- 3. Generate CMake/Comp DB: $ xmake generate_cmakelists_and_compile_commands
target("reaper_imgui_extra_myaddon_x64")
  set_arch("x64")
  set_kind("shared")
  set_plat(os.host())
  set_optimize("fastest") -- none, faster, fastest, smallest
  set_languages("c99", "cxx17")
  add_files("src/*.cpp")
  add_files("src/widgets/*.cpp")
  add_files("src/widgets/color-themes/*.cpp")
  add_includedirs("./vendor/reaimgui")
  add_includedirs("./vendor/reaper-sdk/sdk")
  add_packages("vcpkg::imgui")
  after_build(function (target)
    import("core.project.task")
    task.run("generate_cmakelists_and_compile_commands")
  end)

task("generate_cmakelists_and_compile_commands")
  on_run(function ()
    import("core.base.task")
    import("core.project.project")
    -- Run only once for all xmake processes
    local tmpfile = os.tmpfile(path.join(os.projectdir(), "plugin.cmake_compile_db.autoupdate"))
    local dependfile = tmpfile .. ".d"
    local lockfile = io.openlock(tmpfile .. ".lock")
    if lockfile:trylock() then
      -- We use task instead of os.exec("xmake") to avoid the project lock
      -- Equivalent to "$ xmake project -k cmakelists"
      print("Updating CMakeLists.txt...")
      task.run("project", {kind = "cmakelists"})
      print("Updating CMakeLists finished")
      -- Equivalent to "$ xmake project -k compile_commands"
      print("Updating compile_commands.json...")
      task.run("project", {kind = "compile_commands"})
      print("Updating compile_commands finished")
      lockfile:close()
    end
  end)
  set_menu({
    usage = "xmake generate_cmakelists_and_compile_commands",
    description = "",
    options = {}
  })


