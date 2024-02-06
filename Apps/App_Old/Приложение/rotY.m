function Coil = rotY(Coil, a)
M = [cos(a) 0 sin(a); 0 1 0; -sin(a) 0 cos(a)];
for i = 1:length(Coil(:,1))
    Coil(i,:) = Coil(i,:)*M;
end
