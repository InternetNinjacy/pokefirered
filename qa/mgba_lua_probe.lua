local f = io.open("mgba-lua-probe.txt", "w")
if f then
  f:write("LUA_PROBE_LOADED\n")
  f:close()
end
console:log("LUA_PROBE_LOADED")
