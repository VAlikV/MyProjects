function [Fi_int,L_int,I_int, Red, Blue, Red1, Blue1, Red2, Blue2] = InterpCircuit(R, L, nfi, nL, I, Nc, eb, er, zeror) % Инетерполяция потоковой функции и контур с током

[Fi, Ll, II] = Transform2D(L, nfi, nL, I);

nfi_int = 2001;
nL_int = 1001;

[Fi_int, L_int] = meshgrid(linspace(-pi,pi,nfi_int), linspace(-L,L,nL_int));

I_int = interp2(Fi,Ll,II,Fi_int,L_int);


Nc = Nc*2;
Max = max(max(I_int));  % Максимальное значение функции потока
Min = min(min(I_int));  % Минимальное значение функции потока
df = (Max-Min)/(Nc+1);  % Шаг витков
Sr = (abs(Max)+abs(Min))/2;
Red = [];               % Контура с током против часовой
Blue = [];              % Контура с током по часовой 

for k = 1:Nc
    K1 = Min+df*k;       % Уровень

    if K1 >= 0
        AA = find((I_int >= (K1-er*Sr) & I_int <= (K1+er*Sr) & I_int >= 0) | (I_int >= (K1+er*Sr) & I_int <= (K1-er*Sr) & I_int < 0));
    else
        AA = find((I_int >= (K1+eb*Sr) & I_int <= (K1-eb*Sr) & I_int >= 0) | (I_int >= (K1-eb*Sr) & I_int <= (K1+eb*Sr) & I_int < 0));
    end

    i = ceil(AA/(nL_int));   % Номера столбцов

    j = mod(AA, nL_int);     % Номера строк
    j(j==0) = nL_int;

    Temp = zeros(length(i),2);

    for a = 1:length(i)
        Temp(a,:) = [L_int(j(a),i(a)) Fi_int(j(a),i(a))];
    end

    if K1 >= zeror %(Max+Min)/2
        Red = [Red; Temp];
    else
        Blue = [Blue; Temp];
    end
end

Lred = length(Red);
Lblue = length(Blue);

if Lred ~= 0
    Red1 = zeros(length(Red(:,1)),3);   % Массивы для записи контура в координатах
    Red2 = zeros(length(Red(:,1)),2);   % Массивы для записи контура в плоскости
    Red1(:,1) = Red(:,1);               % X
    Red1(:,2) = R*sin(Red(:,2));        % Y
    Red1(:,3) = R*cos(Red(:,2));        % Z

    Red2(:,1) = Red(:,1);               % X
    Red2(:,2) = Red(:,2)*R;             % R
else
    Red1 = [];
    Red2 = [];
end

if Lblue ~= 0
    Blue1 = zeros(length(Blue(:,1)),3); % Массивы для записи контура в координатах 
    Blue2 = zeros(length(Blue(:,1)),2); % Массивы для записи контура в плоскости
    Blue1(:,1) = Blue(:,1);             % X
    Blue1(:,2) = R*sin(Blue(:,2));      % Y
    Blue1(:,3) = R*cos(Blue(:,2));      % Z

    Blue2(:,1) = Blue(:,1);             % X
    Blue2(:,2) = R*Blue(:,2);           % R
else
    Blue1 = [];
    Blue2 = [];
end
     
