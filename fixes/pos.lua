-- @note: this can be optimized, do it yourself =]

-- @note: if something is further than hammer map limits (32768)
-- game will fail to set pos correctly, and will start spewing messages
-- yapping about "unreasonable position" blah blah
hook.Add("Tick", "a", function()
    for k, v in ents.Iterator() do
        local pos = ent:GetPos() -- @note: lua->c->lua
        local x, y, z = pos.x, pos.y, pos.z -- @note: 3 __index calls
        
        if x == 32768 or y == 32768 or z == 32768 then ent:SetPos(0, 0, 0) end
    end
end)