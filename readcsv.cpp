/* 
    Thanks tetsuyanbo
    https://www.tetsuyanbo.net/tetsuyanblog/23821
    C++メモ STLをできるだけ使ってCSVを読み込んでみる
 */

// インクルード
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要
// 名前空間
using namespace std;
//
//  CSVを取得する
//      filename    読み込むファイル名
//      table       読み込んだCSVの内容
//      delimiter   区切り文字(今回はデフォルトでカンマ)
//
bool GetContents(const string& filename, vector<vector<string>>& table, const char delimiter = ',')
{
	// ファイルを開く
	fstream filestream(filename);
	if (!filestream.is_open())
	{
		// ファイルが開けなかった場合は終了する
		return false;
	}

	// ファイルを読み込む
	while (!filestream.eof())
	{
		// １行読み込む
		string buffer;
		filestream >> buffer;

		// ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
		vector<string> record;              // １行分の文字列のリスト
		istringstream streambuffer(buffer); // 文字列ストリーム
		string token;                       // １セル分の文字列
		while (getline(streambuffer, token, delimiter))
		{
			// １セル分の文字列をリストに追加する
			record.push_back(token);
		}

		// １行分の文字列を出力引数のリストに追加する
		table.push_back(record);
	}

	return true;
}
//
// メインメソッド
//
int main(int argc, const char * argv[])
{
	// 変数を定義する
	bool status = false;    // メソッドのステータス
	string filename = "sample.csv"; // ファイル名
	vector<vector<string>> table;   // 読み込んだCSVファイルの内容

	// CSVファイルの内容を取得する
	status = GetContents(filename, table);
	if (!status)
	{
		// 取得に失敗した場合はエラー終了する
		return -1;
	}

	// 確認のためにコンソールに内容を出力する
	for (int row = 0; row < table.size(); row++)
	{
		vector<string> record;  // １行分の内容
		record = table[row];    // １行分読み込む
		// １セルずつ読み込んでコンソールに出力する
		for (int column = 0; column < record.size(); column++)
		{
			cout << record[column];
			// 末尾の列でない場合はカンマを出力する
			if (column < record.size() - 1)
			{
				cout << ",";
			}
		}
		cout << endl;
	}

	return 0;
}
