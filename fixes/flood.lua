net_Incoming = net_Incoming or net.Incoming

local flood = {}
flood.max = 250
flood.drain = 3

-- @note: prevents basic dos through net
-- won't protect if sv code was written badly
net.Incoming = function(len, client)
    flood[client] = flood[client] + 1
    
    timer.Simple(flood.drain, function()
        if not IsValid(client) then return end
        flood[client] = flood[client] - 1
    end)

    if flood[client] >= flood.max then
        client:Kick("i don't like you")
    end

    net_Incoming(len, client)
end