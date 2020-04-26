// PricingCore.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "Argument.h"
#include "option.h"

int main()
{
    std::cout << "Hello World!\n";
    Argument<double> argDouble;
    argDouble.add("expiry", 1);
    argDouble.add("strike", 100);

    std::cout << "strike: " << argDouble.get("strike") << std::endl;
    std::cout << "used all arguments: " << argDouble.usedAllArguments() << std::endl;
    std::cout << "expiry: " << argDouble.get("expiry") << std::endl;
    std::cout << "used all arguments: " << argDouble.usedAllArguments() << std::endl;
    std::cout << std::endl;

    Argument<std::string> argString;
    argString.add("type", "call");
    std::cout << "type: " << argString.get("type") << std::endl;
    std::cout << "used all arguments: " << argString.usedAllArguments() << std::endl;
    std::cout << std::endl;

    ArgumentContainer arg;
    arg.addDouble("expiry", 1);
    arg.addDouble("strike", 100);
    arg.addString("type", "call");

    std::cout << "strike: " << arg.getDouble("strike") << std::endl;
    std::cout << "used all arguments: " << arg.usedAllArguments() << std::endl;
    std::cout << "type: " << arg.getString("type") << std::endl;
    std::cout << "used all arguments: " << arg.usedAllArguments() << std::endl;
    std::cout << "expiry: " << arg.getDouble("expiry") << std::endl;
    std::cout << "used all arguments: " << arg.usedAllArguments() << std::endl;
    std::cout << std::endl;

    ArgumentContainer argTest;
    argTest.addString("type", "test");
    std::cout << "used all arguments: " << argTest.usedAllArguments() << std::endl;
    std::cout << "price: " << pricing(argTest) << std::endl;
    std::cout << "used all arguments: " << argTest.usedAllArguments() << std::endl;
    std::cout << std::endl;

    ArgumentContainer argCall;
    argCall.addString("type", "call");
    argCall.addDouble("expiry", 1);
    argCall.addDouble("strike", 100);
    argCall.addDouble("spot", 100);
    argCall.addDouble("vol", 0.3);
    argCall.addDouble("risk_free", 0.02);
    argCall.addDouble("npath", 10000);
    std::cout << "price: " << pricing(argCall) << std::endl;
    std::cout << std::endl;

    ArgumentContainer argPut;
    argPut.addString("type", "put");
    argPut.addDouble("expiry", 1);
    argPut.addDouble("strike", 100);
    argPut.addDouble("spot", 100);
    argPut.addDouble("vol", 0.3);
    argPut.addDouble("risk_free", 0.02);
    argPut.addDouble("npath", 10000);
    std::cout << "price: " << pricing(argPut) << std::endl;
    std::cout << std::endl;

    ArgumentContainer argDD;
    argDD.addString("type", "double_digital");
    argDD.addDouble("expiry", 1);
    argDD.addDouble("strike1", 70);
    argDD.addDouble("strike2", 130);
    argDD.addDouble("spot", 100);
    argDD.addDouble("vol", 0.3);
    argDD.addDouble("risk_free", 0.02);
    argDD.addDouble("npath", 10000);
    std::cout << "price: " << pricing(argDD) << std::endl;
    std::cout << std::endl;

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
