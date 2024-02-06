function figWeb = PointWebROI( Node, S, ROI, lx, ly, lz, center, figWeb) % Отрисовка точек, элементов и ROI

if figWeb ~= 0
    figHandles = findall(groot, 'Type', 'figure');
    f = find(figHandles == figWeb);
    if ~isnan(f)
        close(figWeb)
    end
end

figWeb = figure('Name', 'Сетка' ,'NumberTitle','off', 'Position', [610 577 580 410]);
plot3(Node(:,1),Node(:,2),Node(:,3),'b.'); % Отрисовка узлов
hold( "on")
xlabel( 'x, мм'), ylabel( 'y, мм'), zlabel('z, мм')
axis("equal")
grid( "on")
for i = 1:length(S(:,1))
    plot3(Node(S(i,:),1),Node(S(i,:),2),Node(S(i,:),3),'r-'); % Отрисовка сетки
end
plot3(ROI(:,1),ROI(:,2),ROI(:,3),'k.'); % Отрисовка ROI
points = [center(1)+lx/2 center(2)-ly/2 center(3)-lz/2;...
    center(1)+lx/2 center(2)-ly/2 center(3)+lz/2;...
    center(1)+lx/2 center(2)+ly/2 center(3)+lz/2;...
    center(1)+lx/2 center(2)+ly/2 center(3)-lz/2;...
    center(1)-lx/2 center(2)+ly/2 center(3)-lz/2;...
    center(1)-lx/2 center(2)+ly/2 center(3)+lz/2;...
    center(1)-lx/2 center(2)-ly/2 center(3)+lz/2;...
    center(1)-lx/2 center(2)-ly/2 center(3)-lz/2];
plot3([points(1,1) points(2,1) points(3,1) points(4,1) points(1,1)], [points(1,2) points(2,2) points(3,2) points(4,2) points(1,2)], [points(1,3) points(2,3) points(3,3) points(4,3) points(1,3)], '--b')
plot3([points(3,1) points(4,1) points(5,1) points(6,1) points(3,1)], [points(3,2) points(4,2) points(5,2) points(6,2) points(3,2)], [points(3,3) points(4,3) points(5,3) points(6,3) points(3,3)], '--b')
plot3([points(5,1) points(6,1) points(7,1) points(8,1) points(5,1)], [points(5,2) points(6,2) points(7,2) points(8,2) points(5,2)], [points(5,3) points(6,3) points(7,3) points(8,3) points(5,3)], '--b')
plot3([points(7,1) points(8,1) points(1,1) points(2,1) points(7,1)], [points(7,2) points(8,2) points(1,2) points(2,2) points(7,2)], [points(7,3) points(8,3) points(1,3) points(2,3) points(7,3)], '--b')



