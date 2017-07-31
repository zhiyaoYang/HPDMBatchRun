#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QProcess>
#include <iostream>
#include <fstream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //read input file and generate array of parameter, record output parameter
    QString input1, input2, input3;
    QStringList outputList,inputInfo1, inputInfo2, inputInfo3;
    int run1 = 0, run2 = 0, run3 = 0;
    double start1 = 0, start2 = 0, start3 = 0;
    double interval1 = 0, interval2 = 0, interval3 = 0;
    QFile iFile("input.txt");
    if(iFile.open(QIODevice::ReadOnly|QIODevice::Text)){

        QTextStream in(&iFile);


        while (!in.atEnd()){
            QString line = in.readLine();
            if(line.startsWith("INPUT")){


                input1 = line.split("\t").at(1);
                input2 = line.split("\t").at(2);
                input3 = line.split("\t").at(3);
            }
            else if(line.startsWith("OUTPUT")){

                outputList = line.split("\t");
                outputList.removeAt(0);
            }

            in.flush();
            iFile.close();
        }

        qDebug()<<"inputs"<<input1<<input2<<input3;
        qDebug()<<"outputs"<<outputList;

    }
    else{
        return 0;
    }
    inputInfo1 = input1.split(":");
    inputInfo2 = input2.split(":");
    inputInfo3 = input3.split(":");

    qDebug()<<inputInfo1<<inputInfo2<<inputInfo3;

    start1 = inputInfo1.at(2).toDouble();
    interval1 = inputInfo1.at(3).toDouble();
    run1 = inputInfo1.at(4).toInt();
    start2 = inputInfo2.at(2).toDouble();
    interval2 = inputInfo2.at(3).toDouble();
    run2 = inputInfo2.at(4).toInt();
    start3 = inputInfo3.at(2).toDouble();
    interval3 = inputInfo3.at(3).toDouble();
    run3 = inputInfo3.at(4).toInt();

    //find corresponding rows in .hpdm file
    //currently only ID w/ variable name, may fail w/ multiple component system
    QString allText, searchLine;
    QStringList lineList,line1,line2,line3;
    QFile hFile("hpdata.hpdm");
    if(hFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream instream(&hFile);

        allText = instream.readAll();
        hFile.close();

        QFile copyFile("hpdata.hpdm");
        copyFile.copy("phdata_copy.hpdm");

        QFile deleteFile("hpdata.hpdm");
        deleteFile.remove();

        QFile newFile("hpdata.hpdm");
        QTextStream writeStream;

        lineList = allText.split("\n");
        int inputLine1 = 0, inputLine2 = 0, inputLine3 = 0;
        for(int i = 0; i < lineList.count();i++){
            searchLine = lineList.at(i);
            if(searchLine.contains(inputInfo1.at(1))){
                inputLine1 = i;
                line1 = searchLine.split("\t");
            }
            else if(searchLine.contains(inputInfo2.at(1))){
                inputLine2 = i;
                line2 = searchLine.split("\t");
            }
            else if(searchLine.contains(inputInfo3.at(1))){
                inputLine3 = i;
                line3 = searchLine.split("\t");
            }
        }
        if(inputLine1 * inputLine2 * inputLine3 == 0){
            return 0;
        }
        else{

        }

        //replace parameter in .hpdm file and run calculation

        int counter = 0;
        for(int o = 0; o < run1; o++){

            line1.replace(6,QString::number(start1 + o * interval1));

            for(int p = 0; p < run2; p++){

                line2.replace(6,QString::number(start2 + p * interval2));

                for(int q = 0; q < run3; q++){

                    line3.replace(6,QString::number(start3 + q * interval3));

                    lineList.replace(inputLine1,line1.join("\t"));
                    lineList.replace(inputLine2,line2.join("\t"));
                    lineList.replace(inputLine3,line3.join("\t"));

                    allText = lineList.join("\n");

                    //run hpdm
                    deleteFile.setFileName("hpdata.hpdm");
                    deleteFile.remove();
                    if(newFile.open(QIODevice::WriteOnly|QIODevice::Text)){
                        writeStream.setDevice(&newFile);
                        writeStream<<allText;
                        writeStream.flush();
                        newFile.close();

                        QProcess proc;
                        proc.setWorkingDirectory("./");
                        auto Command = QString("cmd.exe");
                        auto Arguments = QStringList{
                                QString("/C"),
                                "RunHPDMFlex.bat"
                        };
                        proc.start(Command,Arguments);
                        proc.waitForFinished(-1);

                        if(proc.exitCode() == 0){
                            qDebug()<<"run complete"<<o<<p<<q;

                            copyFile.setFileName("out.xls");
                            if(!copyFile.copy("./batchResults/out"
                                          +QString::number(counter)
                                          +".xls")){
                                    qDebug()<<"copy error";
                            }
                            else{
                                counter++;
                            }


                        }
                        else{
                            qDebug()<<"run faulty"<<o<<p<<q;
                        }
                    }
                    else{
                        qDebug()<<"fail to write new hpdm file";
                        return 0;
                    }

                    //extract interested results from .out file and put into output file
                }
            }
        }
    }
    else{
        return 0;
    }




    std::string exit;

    std::cout<<"\n\n exit?";
    std::cin>>exit;

    return 0;
}
