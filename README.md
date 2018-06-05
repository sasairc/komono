komono
======

小物（こもの）って言葉、可愛くありませんか？

### waiting

チョット待ってね。

```
% gcc -O2 -Wall -Wextra waiting.c -lbenly_spinner -lbenly_string -o waiting
```

### mbhead

`head(1)`の`-c, --byte`を`--characters`に置き換えたもの。マルチバイト文字対応なのです。

```shellsession
% gcc mbhead.c -o mbhead
% yasuna -n 4337
病院に向かう途中の犬の散歩！ほら！こっち来い！
% yasuna -n 4337 | heac -c 10
病院にå
% yasuna -n 4337 | ./mbhead -c 10
病院に向かう途中の犬
```

### body

`head(1)`と`tail(1)`があるのに、`body`が無いなんておかしい（おかしくない）ので作ったやつ

```shellsession
% gcc body.c -o body
% ./body -v -n 24 ~/Documents/horagai
==> Documents/horagai <==
私の後からも洗った火山灰ー、願いー
それから、私はそれを排出します
お、追って待つことができてぇあって、とても重要なところを洗って忘れていて
え、重要な地方…？
いくつのtobokeテンで、ko↑ko↑ウォッシャブル
明らかでしたの…
菅野米穂
何もない...。 .........
少しもなくカーブ。--
三浦は神経質になりますか？
そうだね…流してくれるか
上がればビールにしたみなよ先輩
そうだねー
おそらく、それは若干の冷水です ......
私がそうであるまさしく今日... ...
ああ、私は冷やされました
あー早くビール音度ー ー. オイ、冷たくなっているのかー？
ア、クェンチャヌムっす、【バー】っ【チェ】てホップですー. ふぅ
三浦、夜間の腹の減らさないだめになることか？
腹は減らしました
エヨ？
ここはiようで、おいしい手打ちうどんの店の商品の屋台、来たのsu
ア、そうなの。ア、ヘンきて得るんだね
行きます
```

### bsodnt4

WindowsNT Workstation 4.0のOS Loader直後からBSODが出るまでを再現したやつ	
ncursesが必要です

```shellsession
% gcc bsodnt4.c -lncurses -o bsodnt4
```

### uescape

`stdin`から読み込んだ文字列のUnicodeのエスケープシーケンスを吐くやつ
glibが必要です

```shellsession
% gcc uescape.c `pkg-config --cflags --libs glib-2.0` -o uescape
% headtail --pretty ~/Documents/sihnyk4
んーイイの時に、それは非常によくイクです。ある。
それはかなり容易でした。
ko↑ko↓
飛んで下さい... 恐ろしいです: 大きいです
私は入ります、そして、彼/それがあなたを喜ばせるならば、
 :
 :
 :
彼はあなたが好きでした！
スマートなすぎいく！それは行きます -- それは行きます -- それは行きます -- それは行きます -- ンアッー！
スマートなそ！
私はよいです！到着はあなたです！胸の本流：そして、胸の上で！
胸の上で動きます
% headtail --pretty ~/Documents/sihnyk4 | ./uescape
\u3093\u30fc\u30a4\u30a4\u306e\u6642\u306b\u3001\u305d\u308c\u306f\u975e\u5e38\u306b\u3088\u304f\u30a4\u30af\u3067\u3059\u3002\u3042\u308b\u3002\u000a\u305d\u308c\u306f\u304b\u306a\u308a\u5bb9\u6613\u3067\u3057\u305f\u3002\u000a\u006b\u006f\u2191\u006b\u006f\u2193\u000a\u98db\u3093\u3067\u4e0b\u3055\u3044\u002e\u002e\u002e\u0020\u6050\u308d\u3057\u3044\u3067\u3059\u003a\u0020\u5927\u304d\u3044\u3067\u3059\u000a\u79c1\u306f\u5165\u308a\u307e\u3059\u3001\u305d\u3057\u3066\u3001\u5f7c\u002f\u305d\u308c\u304c\u3042\u306a\u305f\u3092\u559c\u3070\u305b\u308b\u306a\u3089\u3070\u3001\u000a\u0020\u003a\u000a\u0020\u003a\u000a\u0020\u003a\u000a\u5f7c\u306f\u3042\u306a\u305f\u304c\u597d\u304d\u3067\u3057\u305f\uff01\u000a\u30b9\u30de\u30fc\u30c8\u306a\u3059\u304e\u3044\u304f\uff01\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u30f3\u30a2\u30c3\u30fc\uff01\u000a\u30b9\u30de\u30fc\u30c8\u306a\u305d\uff01\u000a\u79c1\u306f\u3088\u3044\u3067\u3059\uff01\u5230\u7740\u306f\u3042\u306a\u305f\u3067\u3059\uff01\u80f8\u306e\u672c\u6d41\uff1a\u305d\u3057\u3066\u3001\u80f8\u306e\u4e0a\u3067\uff01\u000a\u80f8\u306e\u4e0a\u3067\u52d5\u304d\u307e\u3059\u000a
% headtail --pretty ~/Documents/sihnyk4 | ./uescape -l
\u3093\u30fc\u30a4\u30a4\u306e\u6642\u306b\u3001\u305d\u308c\u306f\u975e\u5e38\u306b\u3088\u304f\u30a4\u30af\u3067\u3059\u3002\u3042\u308b\u3002
\u305d\u308c\u306f\u304b\u306a\u308a\u5bb9\u6613\u3067\u3057\u305f\u3002
\u006b\u006f\u2191\u006b\u006f\u2193
\u98db\u3093\u3067\u4e0b\u3055\u3044\u002e\u002e\u002e\u0020\u6050\u308d\u3057\u3044\u3067\u3059\u003a\u0020\u5927\u304d\u3044\u3067\u3059
\u79c1\u306f\u5165\u308a\u307e\u3059\u3001\u305d\u3057\u3066\u3001\u5f7c\u002f\u305d\u308c\u304c\u3042\u306a\u305f\u3092\u559c\u3070\u305b\u308b\u306a\u3089\u3070\u3001
\u0020\u003a
\u0020\u003a
\u0020\u003a
\u5f7c\u306f\u3042\u306a\u305f\u304c\u597d\u304d\u3067\u3057\u305f\uff01
\u30b9\u30de\u30fc\u30c8\u306a\u3059\u304e\u3044\u304f\uff01\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u305d\u308c\u306f\u884c\u304d\u307e\u3059\u0020\u002d\u002d\u0020\u30f3\u30a2\u30c3\u30fc\uff01
\u30b9\u30de\u30fc\u30c8\u306a\u305d\uff01
\u79c1\u306f\u3088\u3044\u3067\u3059\uff01\u5230\u7740\u306f\u3042\u306a\u305f\u3067\u3059\uff01\u80f8\u306e\u672c\u6d41\uff1a\u305d\u3057\u3066\u3001\u80f8\u306e\u4e0a\u3067\uff01
\u80f8\u306e\u4e0a\u3067\u52d5\u304d\u307e\u3059
```

### nyancat

`stdin`から読み込んだ文字列を`n_cipher`でエンコードし、任意ホストの任意TCPポートへなげるやつ。	
libncipherが必要です。

```shellsession
% gcc nyancat.c -o nyancat -lncipher
% renge -l | body | ./nyancat -p 2048 localhost &
[1] 14830 14831 14832
% nc localhost 2048
んにぱ〜ゃすぱ〜んにゃ〜ゃゃん〜ぱすすゃにん〜ぱすすんにに〜ぱすすにゃぱ〜ぱすぱすゃゃ〜ぱすすんにに〜
:
:
:
```

### rsync_mirroring

`rsync`と`cron`での簡易的な時間差ミラーリング。適当なスケジュールで登録して下さい。

#### options

```shellsession
SRC=(DIR ..)    # 対象とするディレクトリ
DEST=(DIR ..)   # 複製先のマウントポイント SRCに基づきディレクトリ階層は維持される
RSYNC_OPT=STR	  # rsyncのコマンドラインオプション
RSYNC_NICE=STR  # niceですね〜 niceですね〜
LOGFILE=PATH    # ログファイルのパス
```

#### example

```shellsession
SRC=("/usr/src" "/var" "/tmp" "/home")	
DEST=("/mnt/backup_1" "/mnt/backup_2" "/mnt/backup_3")
RSYNC="/usr/bin/rsync"
RSYNC_OPT="-av --delete --exclude lost+found"
LOGFILE="/var/log/rsync_backup.log"
```

### tateyomi

標準入力から読んだ文章を改行区切りで縦読みにし、標準出力へ書き込みます。

```shellsession
% gcc tateyomi.c -lbenly_typestring -o tateyomi
% < amenimomakezu.txt
雨ニモマケズ
風ニモマケズ
雪ニモ夏ノ暑サニモマケヌ
丈夫ナカラダヲモチ
慾ハナク
決シテ瞋ラズ
イツモシヅカニワラッテヰル
一日ニ玄米四合ト
味噌ト少シノ野菜ヲタベ
アラユルコトヲ
ジブンヲカンジョウニ入レズニ
ヨクミキキシワカリ
ソシテワスレズ
小サナ萓ブキノ小屋ニヰテ
東ニ病気ノコドモアレバ
行ッテ看病シテヤリ
西ニツカレタ母アレバ
行ッテソノ稲ノ朿ヲ負ヒ
南ニ死ニサウナ人アレバ
行ッテコハガラナクテモイヽトイヒ
北ニケンクヮヤソショウガアレバ
ツマラナイカラヤメロトイヒ
ヒドリノトキハナミダヲナガシ
サムサノナツハオロオロアルキ
ミンナニデクノボートヨバレ
ホメラレモセズ
クニモサレズ
サウイフモノニ
ワタシハナリタイ
% < amenimomakezu.txt ./tateyomi
ワサクホミサヒツ北行南行西行東小ソヨジア味一イ決慾丈雪風雨
タウニメンムドマニッニッニッニサシクブラ噌日ツシハ夫ニニニ
シイモラナサリラケテ死テツテ病ナテミンユトニモテナナモモモ
ハフサレニノノナンコニソカ看気萓ワキヲル少玄シ瞋クカ夏ママ
ナモレモデナトイクハサノレ病ノブスキカコシ米ヅラ　ラノケケ
リノズセクツキカヮガウ稲タシコキレシントノ四カズ　ダ暑ズズ
タニ　ズノハハラヤラナノ母テドノズワジヲ野合ニ　　ヲサ　　
イ　　　ボオナヤソナ人朿アヤモ小　カョ　菜トワ　　モニ　　
　　　　ーロミメシクアヲレリア屋　リウ　ヲ　ラ　　チモ　　
　　　　トオダロョテレ負バ　レニ　　ニ　タ　ッ　　　マ　　
　　　　ヨロヲトウモバヒ　　バヰ　　入　ベ　テ　　　ケ　　
　　　　バアナイガイ　　　　　テ　　レ　　　ヰ　　　ヌ　　
　　　　レルガヒアヽ　　　　　　　　ズ　　　ル　　　　　　
　　　　　キシ　レト　　　　　　　　ニ　　　　　　　　　　
　　　　　　　　バイ　　　　　　　　　　　　　　　　　　　
　　　　　　　　　ヒ　　　　　　　　　　　　　　　　　　　
```

### uldebrepo

scp でリモートの apt リポジトリへアップロードするのが地味に面倒なのを簡略化するやつ。
