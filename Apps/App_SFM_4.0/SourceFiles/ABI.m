function I = ABI(L, R, lx, ly, lz, N, Node, S, Rsp, ROI, ro, t, alpfa, betta, Bdes, form) % Вычисление матрицы коэффициентво

order_web = log10(sqrt(L*R/(0.0555*0.15)));
switch form
    case 0
        order_ROI = log10(nthroot((lx*ly*lz)/(0.066*0.066*0.066),3));
    case 1 
        order_ROI = log10(Rsp/0.033);
    case 2
        order_ROI = log10(Rsp/0.033);
end

gamma = -11*order_web + 4*order_ROI;
tetta = -10*order_web + 4*order_ROI;

alpfa = alpfa*10^gamma;
betta = betta*10^tetta;

% Задание матрицы А
A = zeros(N,N);
parfor j = 1:N
    for i = 1:N
        bz1 = Calcbz(i, S, Node, ROI);
        bz2 = Calcbz(j, S, Node, ROI);
        Lmn = CalcLmn(i, j, S, Node);
        pmn = CalcPmn(i, j, ro, t, S, Node);
        Arr = bz1.*bz2;
        A(i,j) = zum(Arr) + alpfa*Lmn + betta*pmn;
    end
end

clear Temp bz1 bz2

% Задание матрицы B

B = zeros(N,1);

for i = 1:N
    bz1 = Calcbz(i, S, Node, ROI);
    Arr = Bdes(:,1).*bz1;
    B(i,1) = zum(Arr);
end 

I = pinv(A)*B;
