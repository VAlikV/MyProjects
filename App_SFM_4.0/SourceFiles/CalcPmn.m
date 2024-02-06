function pmn = CalcPmn(n, m, ro, t, S, Node) % Параметр p 
Sin = N2T(n, S);
Sim = N2T(m, S);
Sum = 0;
for i=1:length(Sim)
    for j=1:length(Sin)
        Arn = Area(S(Sin(j),:),Node);
        Arm = Area(S(Sim(i),:),Node);
        Jn = CalcJn(n, S(Sin(j),:), Node);
        Jm = CalcJn(m, S(Sim(i),:), Node);
        if Sim(i)==Sin(j)
            Sum = Sum + ScalarP(Jn(1,:),Jm(1,:))*Arn;
        end
    end
end
pmn = Sum*(ro/t);
