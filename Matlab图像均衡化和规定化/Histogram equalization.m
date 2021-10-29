close all; clear all; clc
%%

f=imread('tree.png');  %��ȡͼ��, �趨ͼ���ļ�λ��
f=rgb2gray(f);         %rgb2gray
x=0:255;               %�趨ͼ�񳤶� (�д�ȷ������) �Ҷ�ֵ����?
num=zeros(1,256);      %�趨ֱ��ͼ(x,y)=�Ҷ�ֵ*������
sum_num1=0;
[a,b]=size(f);   %����ͼ��   ��a  *  ��b,
for i=0:255   %���ػҶ�ֵ
    for j=1:a
        for m=1:b
            if f(j,m)==i     %ȷ��ͼ���ĳ�����صĻҶ�ֵ
                num(i+1)=num(i+1)+1;   %iΪ0��255,ͳ�Ƹ��Ҷ�ֵ�ĸ���
            end
        end
    end
end
sum_num=a*b;  %������������
subplot(2,2,1),bar(x,num/sum_num,0.875),title('ԭʼֱ��ͼ');

%ֱ��ͼ���⻯
num1=zeros(1,256);
num2=zeros(1,256);
for i=1:256
    for j=1:i
        sum_num1=sum_num1+num(j);  %�ۼ�ֱ��ͼ
    end
    num1(i)=round(255*sum_num1/sum_num); %ȡ��
    sum_num1=0;
end
for i=1:256
    num2(i)=sum(num(num1==(i-1)));
end
subplot(2,2,3),bar(x,num2/sum_num,0.875),title('���⻯ֱ��ͼ');

%���⻯���ͼ��
f_new=f;
for i=0:255
    f_new(f==i)=num1(i+1); %�ҳ�ԭͼ���ص�λ�ã������⻯������������Ӧλ��
end
subplot(2,2,2),imshow(f);title('ԭʼͼ��')
subplot(2,2,4),imshow(f_new);title('���⻯���ͼ��')


imwrite(f_new, 'tree_new.png')