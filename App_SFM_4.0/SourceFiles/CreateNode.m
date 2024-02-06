function Node = CreateNode(R, L, nfi, nL, axial) % Создание массива узлов
Node = zeros(nfi,3); % Сетка
Temp = zeros(nfi,3); 

f = linspace(-pi+2*pi/nfi,pi,nfi); % Массив значений угла
l = linspace(-L,L,nL); % Массив значений длины

Node(:,1) = l(1);      % X
Node(:,2) = R*sin(f);  % Y
Node(:,3) = R*cos(f);  % Z

for i = 2:nL
    Temp(:,1) = l(i); % X
    Temp(:,2) = R*sin(f); % Y        
    Temp(:,3) = R*cos(f); % Z
    Node = [Node; Temp];
end

if axial
    Node = rotY(Node, pi/2); % Поворот катушки
end

