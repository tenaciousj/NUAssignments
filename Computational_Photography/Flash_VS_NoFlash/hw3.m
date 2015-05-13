white = double(imread('hw36White.jpg'))/255.0;
black = double(imread('hw37Black.jpg'))/255.0;

a = 0.25; %range (intensity) domain, [0.05, 0.25]
b = 64; %spatial domain, [1, 64]

%Denoise each color channel separately

%no flash picture denoised
%red channel
black_filtered(:,:,1) = bilateralFilter(black(:,:,1), a, b);
%green channel
black_filtered(:,:,2) = bilateralFilter(black(:,:,2), a, b);
%blue channel
black_filtered(:,:,3) = bilateralFilter(black(:,:,3), a, b);

%flash picture denoised
%red channel
white_filtered(:,:,1) = bilateralFilter(white(:,:,1), a, b);
%green channel
white_filtered(:,:,2) = bilateralFilter(white(:,:,2), a, b);
%blue channel
white_filtered(:,:,3) = bilateralFilter(white(:,:,3), a, b);

%Equation 1 specified in Part 3
result = (black_filtered).*((white+0.02)./(white_filtered+0.02));

%show the resulting picture
imshow(result);