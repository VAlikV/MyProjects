function ROI = CreateSphereROI(nR, nksi, ntetta, R, CenterROI) % Создание сферического массива ROI
    PolarROI = [];
    dR = R/(nR-1);
    dtetta = pi/(ntetta-1);
    ksi = transpose(linspace(-pi,pi-2*pi/nksi,nksi));
    
    for j = 1:ntetta
        t = -pi+(j-1)*dtetta;
        for i = 1:nR
            r = (i-1)*dR;
            Temp = [r*ones(nksi,1) ksi t*ones(nksi,1)];
            PolarROI = [PolarROI; Temp];
        end
    end
    
    ROI = zeros(length(PolarROI),3);
    
    ROI(:,1) = PolarROI(:,1).*cos(PolarROI(:,2)).*sin(PolarROI(:,3)) + CenterROI(1);
    ROI(:,2) = PolarROI(:,1).*sin(PolarROI(:,2)).*sin(PolarROI(:,3)) + CenterROI(2);
    ROI(:,3) = PolarROI(:,1).*cos(PolarROI(:,3)) + CenterROI(3);
end