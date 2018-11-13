
local delta = 3;
local boost_mp = 1.5;
local xpos = 241;
local ypos = 241;

function draw()
    
    background(255, 0, 0);
    
    if(input.space == 1)then
        drawsquare(xpos, ypos, 30, 30, 0, 255, 0);
    else
        drawsquare(xpos, ypos, 30, 30, 0, 0, 255);
    end
    
end


function update30()
    
    if(input.space == 1)then
        xpos = xpos + (input.x * delta * boost_mp);
        ypos = ypos + (input.y * delta * boost_mp);
    else
        xpos = xpos + (input.x * delta);
        ypos = ypos + (input.y * delta);
    end
    
end