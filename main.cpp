#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //read input file and generate array of parameter, record output parameter


    QFile iFile("input.txt");
    if(iFile.open(QIODevice::ReadOnly)){

        if(!oFile.open(QIODevice::WriteOnly)){
            std::cout<<"failed to open output file.\n";
            write = false;
        }
        std::cout<<"input parameters are:\n";

        QTextStream in(&iFile);

        std::string str;

        QString ref_s, sorb_s, tK_s, xMass_s;

        while (!in.atEnd()){
            QString line = in.readLine();
            if(line.startsWith("ref/sorb")){

                if(write){
                    out<<line<<'\n';
                    out<<"t[K]\tmass ratio\tp[kPa]\tequation form\treference\n";
                }

                ref_s = line.split("\t").at(1);
                sorb_s = line.split("\t").at(2);

                ref = ref_s.toStdString();
                sorb = sorb_s.toStdString();
            }
            else if(line.at(0).isDigit()){
                tK_s= line.split("\t").at(0);
                tK = tK_s.toDouble();
                xMass_s = line.split("\t").at(1);
                xMass = xMass_s.toDouble();


                if(write){
                    out<<QString::fromStdString(str);
                }
            }

            in.flush();
            iFile.close();
        }


        //replace parameter in .hpdm file and run calculation

        //extract interested results from .out file and put into output file

    }

    std::cout<<"\n\n exit?";
    std::cin>>exit;

    return a.exec();
}
