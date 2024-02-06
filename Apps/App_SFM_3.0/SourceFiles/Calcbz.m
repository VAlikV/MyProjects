function bz = Calcbz(n, S, Node, ROI) % Параметр b 
Si = N2T(n, S); % 
Sum = zeros(length(ROI(:,1)),1);
point = zeros(4,3);
w = [-9/32 25/96 25/96 25/96];
for i=1:length(Si)
    integral = zeros(length(ROI(:,1)),1);  
    Jn = CalcJn(n, S(Si(i),:), Node);
    r1 = [Node(S(Si(i),1),1) Node(S(Si(i),1),2) Node(S(Si(i),1),3)]; 
    r2 = [Node(S(Si(i),2),1) Node(S(Si(i),2),2) Node(S(Si(i),2),3)];  
    r3 = [Node(S(Si(i),3),1) Node(S(Si(i),3),2) Node(S(Si(i),3),3)];
    point(1,:) = (r1 + r2 - 2*r3)/3 + r3;
    point(2,:) = 3*(r1 - r3)/5 + (r2 - r3)/5 + r3;
    point(3,:) = (r1 - r3)/5 + 3*(r2 - r3)/5 + r3;
    point(4,:) = (r1 + r2 - 2*r3)/5 + r3;      
    for j = 1:4
        d = DistanceROI(point(j,:),ROI);
        integral = integral + (w(j)*(Jn(1,2)*(ROI(:,1)-point(j,1))-Jn(1,1)*(ROI(:,2)-point(j,2))))./(d.^3);
    end      
    Sum = Sum + integral;
end
bz = Sum*(10^(-7));
