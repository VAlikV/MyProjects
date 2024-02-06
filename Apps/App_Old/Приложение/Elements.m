function Elements(I, S, Node) % Отрисовка элементов

rgb = ones(length(S(:,1)),3);

StFun = zeros(length(S(:,1)),1);

for i = 1:length(S(:,1))
    StFun(i,1) = (I(S(i,1),1) + I(S(i,2),1) + I(S(i,3),1))/3; 
end

StFun = StFun - min(min(StFun));
StFun = 0.6667*StFun/max(max(StFun));

for i = 1:length(S(:,1))
    rgb(i,:) = hsv2rgb([StFun(i,1) 1 1]);
end

figure('Name','Элементы','NumberTitle','off'); 
movegui([0 30]);
x = [Node(S(1,1),1) Node(S(1,2),1) Node(S(1,3),1)];
y = [Node(S(1,1),2) Node(S(1,2),2) Node(S(1,3),2)];
z = [Node(S(1,1),3) Node(S(1,2),3) Node(S(1,3),3)];
fill3(x, y, z,rgb(1,:))
hold on
xlabel ('x [m]'), ylabel ('y [m]'), zlabel ('z [m]')
axis equal
grid on
for i = 2:length(S(:,1))
    x = [Node(S(i,1),1) Node(S(i,2),1) Node(S(i,3),1)];
    y = [Node(S(i,1),2) Node(S(i,2),2) Node(S(i,3),2)];
    z = [Node(S(i,1),3) Node(S(i,2),3) Node(S(i,3),3)];
    fill3(x, y, z,rgb(i,:)) % Отрисовка элементов
end
