function Coil = rotZ(Coil, a)
M = [cos(a) -sin(a) 0; sin(a) cos(a) 0; 0 0 1];
for i = 1:length(Coil(:,1))
    Coil(i,:) = Coil(i,:)*M;
end
