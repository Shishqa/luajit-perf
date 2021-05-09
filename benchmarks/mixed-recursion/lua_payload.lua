local M = {}

-- fibonacci number
function M.payload(n)
    if n == 0 then
        return 0
    elseif n == 1 then
        return 1
    end
    return M.payload(n - 1) + M.payload(n - 2)
end

return M
