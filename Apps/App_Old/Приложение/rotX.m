function Coil = rotX(Coil, a)
M = [1 0 0; 0 cos(a) -sin(a); 0 sin(a) cos(a)];
for i = 1:length(Coil(:,1))
    Coil(i,:) = Coil(i,:)*M;
end
