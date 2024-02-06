function Jn = CalcJn(n, St, Node) % Базисный вектор тока
t = find(St == n);
Jn = zeros(2,3);
Ar = Area(St, Node);
if t == 1
    Jn(1,:) = (Node(St(3),:)-Node(St(2),:))/(2*Ar);
    Jn(2,:) = Node(St(2),:);
elseif t == 2
    Jn(1,:) = (Node(St(1),:)-Node(St(3),:))/(2*Ar);
    Jn(2,:) = Node(St(3),:);
elseif t == 3
    Jn(1,:) = (Node(St(2),:)-Node(St(1),:))/(2*Ar);
    Jn(2,:) = Node(St(1),:);
else
    disp('___ОШИБКА ВЫБОРА УЗЛА/ЭЛЕМЕНТА___');
end
