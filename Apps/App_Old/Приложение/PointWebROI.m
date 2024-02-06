function PointWebROI(Node, S, ROI) % Отрисовка точек, элементов и ROI
% n = 25;
%Si = N2T(n, S); 

figure('Name','Сетка','NumberTitle','off'); 
movegui([0 560]);
plot3(Node(:,1),Node(:,2),Node(:,3),'b.'); % Отрисовка узлов
hold on
xlabel ('x [m]'), ylabel ('y [m]'), zlabel ('z [m]')
axis equal
grid on 
%plot3(Node(S(Si,:),1),Node(S(Si,:),2),Node(S(Si,:),3),'g*'); % Отрисовка элемента (N2T) 
for i = 1:length(S(:,1))
    plot3(Node(S(i,:),1),Node(S(i,:),2),Node(S(i,:),3),'r-'); % Отрисовка сетки
end
plot3(ROI(:,1),ROI(:,2),ROI(:,3),'k.'); % Отрисовка ROI
