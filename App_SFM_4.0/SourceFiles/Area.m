function Ar = Area(St, Node) % Возвращает площадь элемента 
S1 = det([1 Node(St(1),1) Node(St(1), 2); 1 Node(St(2),1) Node(St(2), 2); 1 Node(St(3),1) Node(St(3), 2)]);
S2 = det([1 Node(St(1),1) Node(St(1), 3); 1 Node(St(2),1) Node(St(2), 3); 1 Node(St(3),1) Node(St(3), 3)]);
S3 = det([1 Node(St(1),2) Node(St(1), 3); 1 Node(St(2),2) Node(St(2), 3); 1 Node(St(3),2) Node(St(3), 3)]);
Ar = 0.5*sqrt(S1^2+S2^2+S3^2);
