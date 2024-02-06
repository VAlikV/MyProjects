function di = DistanceROI(Node, ROI) % Расстояние между двумя узлами
di = sqrt((Node(1)-ROI(:,1)).^2+(Node(2)-ROI(:,2)).^2+(Node(3)-ROI(:,3)).^2);
