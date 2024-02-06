function Lmn = CalcLmn(n, m, S, Node) % Параметр Lmn 
Sin = N2T(n, S);
Sim = N2T(m, S);
Sum = 0;
for i=1:length(Sim)
    for j=1:length(Sin)
        Arn = Area(S(Sin(j),:),Node);
        Arm = Area(S(Sim(i),:),Node);
        Jn = CalcJn(n, S(Sin(j),:), Node);
        Jm = CalcJn(m, S(Sim(i),:), Node);
        rn = [(Node(S(Sin(j),1),1)+Node(S(Sin(j),2),1)+Node(S(Sin(j),3),1))/3 ...
            (Node(S(Sin(j),1),2)+Node(S(Sin(j),2),2)+Node(S(Sin(j),3),2))/3 ...
            (Node(S(Sin(j),1),3)+Node(S(Sin(j),2),3)+Node(S(Sin(j),3),3))/3];

        rm = [(Node(S(Sim(i),1),1)+Node(S(Sim(i),2),1)+Node(S(Sim(i),3),1))/3 ...
            (Node(S(Sim(i),1),2)+Node(S(Sim(i),2),2)+Node(S(Sim(i),3),2))/3 ...
            (Node(S(Sim(i),1),3)+Node(S(Sim(i),2),3)+Node(S(Sim(i),3),3))/3];
        d = Distance(rn, rm);
        if Sim(i)~=Sin(j)
            Sum = Sum + ScalarP(Jn(1,:),Jm(1,:))*Arn*Arm/d;
        else
            r1 = Node(S(Sim(i),1),:);
            r2 = Node(S(Sim(i),2),:);
            r3 = Node(S(Sim(i),3),:);
            aa = ScalarP((r3-r1),(r3-r1));
            bb = ScalarP((r3-r1),(r3-r2));
            cc = ScalarP((r3-r2),(r3-r2));
            p1 = sqrt(aa*cc);
            p2 = sqrt(aa-2*bb+cc);
            Sum = Sum + (4*ScalarP(Jn(1,:),Jm(1,:))*Arn*Arm)*((1/(6*sqrt(aa)))*log(((aa-bb+sqrt(aa)*p2)*(bb+p1))/((-bb+p1)*(-aa+bb+sqrt(aa)*p2)))+...
                (1/(6*sqrt(cc)))*log(((bb+p1)*(-bb+cc+sqrt(cc)*p2))/((bb-cc+sqrt(cc)*p2)*(-bb+p1)))+...
                (1/(6*p2))*log(((aa-bb+sqrt(aa)*p2)*(-bb+cc+sqrt(cc)*p2))/((bb-cc+sqrt(cc)*p2)*(-aa+bb+sqrt(aa)*p2))));
        end
    end
end
Lmn = Sum*(10^(-7));
