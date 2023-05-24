local read = io.read
local write = io.write

math.randomseed(os.time())

local seq_len = read("*n")
local intv_start_min = read("*n")
local intv_start_max = read("*n")
local intv_len_min = read("*n")
local intv_len_max = read("*n")

for _ = 1, seq_len do
  local intv_start = math.random(intv_start_min, intv_start_max)
  local intv_len = math.random(intv_len_min, intv_len_max)
  local intv_end = intv_start + intv_len - 1;

  write(intv_start .. ' ' .. intv_end .. '\n')
end
