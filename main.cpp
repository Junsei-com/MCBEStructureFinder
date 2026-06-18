#include <iostream>
#include <cmath>
#include "be_finder.h"
#include "structure.h"

int main() {
    // 1. 統合版のシミュレータを初期化 (1.18以降の構造物生成に対応)
    // ※MCBEStructureFinderの基本セットアップ
    init_be_finder(); 

    std::cout << "⚡ 統合版 1.21対応：初期スポーン20マス以内の荒廃したポータルを走査中...\n";
    std::cout << "--------------------------------------------------------\n";

    // 2. シード値を0から順番にPCの限界速度でループ
    // とりあえず1億個（100,000,000）スキャンしてみます
    for (uint64_t seed = 0; seed < 100000000; ++seed) {
        
        // 荒廃したポータル（Ruined Portal）の初期リージョン(0,0)での座標を取得
        // 内部の関数名や構造体はリポジトリの定義（structure.h / be_finder.h）に準拠
        BlockPos pos = get_structure_pos(RUINED_PORTAL, seed, 0, 0);

        // 座標が正常に取得できなかった場合はスキップ
        if (pos.x == -1 && pos.z == -1) continue;

        // 📐 三平方の定理で初期スポーン（0,0）からの直線距離を計算
        double distance = std::sqrt(pos.x * pos.x + pos.z * pos.z);

        // 【ここが核心】距離が20マス以内のシードだけを容赦なく画面に引きずり出す！
        if (distance <= 20.0) {
            std::cout << "🎯 【神シード発見】 Seed: " << seed 
                      << " (座標 X: " << pos.x << ", Z: " << pos.z 
                      << " / スポーンからの距離: " << distance << "マス)\n";
        }
    }

    std::cout << "--------------------------------------------------------\n";
    std::cout << "走査が完了しました。\n";
    return 0;
}
