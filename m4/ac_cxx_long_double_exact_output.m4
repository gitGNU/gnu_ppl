dnl A function to detect whether C++ provides exact output for long doubles.
dnl Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .

AC_DEFUN([AC_CXX_LONG_DOUBLE_EXACT_OUTPUT],
[
AC_REQUIRE([AC_C_BIGENDIAN])
AC_REQUIRE([AC_CXX_LONG_DOUBLE_BINARY_FORMAT])
ac_save_CPPFLAGS="$CPPFLAGS"
ac_save_LIBS="$LIBS"
AC_LANG_PUSH(C++)

AC_MSG_CHECKING([whether C++ provide exact output for long doubles])
ac_cxx_long_double_exact_output=unknown

AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <limits>
#ifdef HAVE_STDINT_H
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS 1
#endif
#include <stdint.h>
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <cstdlib>
#include <sstream>
#include <iostream>

/* Unique (nonzero) code for the IEEE 754 Single Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_SINGLE 1

/* Unique (nonzero) code for the IEEE 754 Double Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_DOUBLE 2

/* Unique (nonzero) code for the IEEE 754 Quad Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_QUAD 3

/* Unique (nonzero) code for the Intel Double-Extended
   floating point format.  */
# define PPL_FLOAT_INTEL_DOUBLE_EXTENDED 4

bool
check(long double value, const char* text) {
  std::ostringstream ss;
  ss.precision(10000);
  ss << value;
  std::cout << ss.str() << " ?==? " << text << std::endl;
  return ss.str() == text;
}

#if SIZEOF_LONG_DOUBLE == 12

long double
convert(uint32_t msp, uint64_t lsp) {
  union {
    long double value;
    struct {
#ifdef WORDS_BIGENDIAN
      uint32_t msp;
      uint64_t lsp;
#else
      uint64_t lsp;
      uint32_t msp;
#endif
    } parts;
  } u;

  u.parts.msp = msp;
  u.parts.lsp = lsp;
  return u.value;
}

#if CXX_LONG_DOUBLE_BINARY_FORMAT == PPL_FLOAT_INTEL_DOUBLE_EXTENDED

int
main() {
  if (check(convert(0xaaacccaaUL, 0xacccaaacccaaacccULL),
            "-23475151196235330448360987288488448023604990597437922665537894499317141030270831473500040521309097782521743811281100731620612303910141158923283064807755815684643856544564541670181998003713114595098650350075763370916908460284838902787487703020001649220669684278577319085319204471093693972621987808779314674903648668236688723332999785552894845325917244897920804830290985291535343986477508649100409893486651507134071296739623686984014433965803259868867855465109457220731656260670349710137932272802677796915669809481885196101414678015638835049035133835457854893845093496950772367562664955830097293678125205138879788670490610650322134182370990336443894886171520732434535881085387893610114822547025980969387956199048733969351859470324032549906964255557877860343871346618951696178837035563054101786829980983909935265617095747543882856776297861197958453847978446679149969948882161264279705948735019353220550905117946051015070744207453853343171175921378515361160726195198161165083475968")
      && check(convert(0xcccaaaccUL, 0xcaaacccaaacccaaaULL),
               "-3.234349908433673569788362433758236701401379200386310478070230491201716094576208088733092209352711081763530973139439402754721006217889031902309566905344106766697050593355851405189694125966100801537593811320493850579152938679705465870788684523518541806158791408378718596936132854683425581754205242594614192465876640102628432246897674583649745467641139234207139584810101868772915312454075582265240687184279243861217351667059920878236164506473261797703393981510799228030778152399657445848839855361831637014754038570644257393307922665529947406582062857348101442206039278033447012163028384634753160589791458287895963629514043345016273218385584012204321293761500625038828699451659598873739820939586314044735551522599884065690704853850058509917597610804664086074437219778400030370474948166770867639885264893441594112815147445129222900623635467542926999246959939000796968650036727515644358583656635086409945418378371210848857160579105176395869221692977516017583375976424496977231821652434877830409470264872174e-1634")
      && check(convert(0x00000000UL, 0x0000000000000001ULL),
               "p")
      && check(convert(0x80000000UL, 0x0000000000000001ULL),
               "q")
      )
    exit(0);
  else
    exit(1);
}

#else // CXX_LONG_DOUBLE_BINARY_FORMAT != FLOAT_INTEL_DOUBLE_EXTENDED

int
main() {
  exit(1);
}

#endif // CXX_LONG_DOUBLE_BINARY_FORMAT != FLOAT_INTEL_DOUBLE_EXTENDED

#elif SIZEOF_LONG_DOUBLE == 16

long double
convert(uint64_t msp, uint64_t lsp) {
  union {
    long double value;
    struct {
#ifdef WORDS_BIGENDIAN
      uint64_t msp;
      uint64_t lsp;
#else
      uint64_t lsp;
      uint64_t msp;
#endif
    } parts;
  } u;

  u.parts.msp = msp;
  u.parts.lsp = lsp;
  return u.value;
}

#if CXX_LONG_DOUBLE_BINARY_FORMAT == PPL_FLOAT_IEEE754_QUAD

int
main() {
  if (check(convert(0xaaacccaaacccaaacULL, 0xccaaacccaaacccaaULL),
            "-8.55855653885100434741341853993902633367349104766375354667159377718342093894815477326286823233135691805519944470138219932524951165689852082013017904043605683486724317550972746307400400204571080045247416605879743573136814766221652651396476675668866980798618379071105211750397249729982891787041148520384572930274879267722158826932337019191713973025403784448443813348692062209940856126724493492803365972504505177354875652033856070760087261648660638833868952644144747756799606849182265604546917705495630867683634260396102823982577953799017062698102242357552179655099799114234932578035799185560231199083485854936098752376968393647581458407558794412029383325763638562788717260040049064497131924995762524305159587498016677454321953274959044696323291625045478494472581264819229447771276640446297211105522340278216491094195598543872903469867733674572559977106495016037365144714092305087690135013719347274733034998868445412589677425060095799279101903473205374412225289846468374532481297065712317082077938035156602646698351182648104255704218634101302925067087078955133405900007044267209898310644310904503791609310204530573463263951434586894153990739119187567218316060343579381319744970284036645819031296341711196622764674251739340075981861518157380656135644972541894187627902651874054588734732906342927804126694032667794810086817870907476586539935233288396561987441453006798066121939082312783518917156845604116991071351557087417820814737448930366014934139649936714605919733198611573267554373841805458030152706709963798138766665437195696286204333504023648063774567253657433115103351104190986192714072985487851579415615609526545777708652951405409847708647802254957197551148967040887700676749608935220270768342493900689974647088468653016844028721111482484905641458435567969469008688175230469940968306817582881926746422674891155765989419578280531847369896579997902056370886853884911608932917273377526774091310024267948445090595150848945937264274298230316059283748541372546998570685254364147022857127106166375807928861080771495427281772909457414476961102929683460150380091022216902985688084496718499522925736236100966839490544989265028487132166444183820209811985298620037327410566483546092567386575203772065259924817078378553423445114795887961447486917127608105936488957460696218995227900239169698156532097505472359601263421630872600694896078087993492528322817946497772710008837719609909497752428441503174822795185219988589528998338631725113908025553153842511443825016809012668839505492083731555461826355018782953670089090573806418379608917728933789667567839232807208925449602517595541397929042673972541764273293287457694772131268012143158809453627483947788463130353101911401667613659585055576869155534998835800762122080588150495103765874874613454517177121048246498282285280904742153700877576028449241385429235777250684782328183787286276152331338688335510090441008799792147837436640030059474106105829612076012626498555138419516242851436828131901668517305064107076254421670883938440896580435257206350630093337919967881954501164988008085285088049681541452106188312639266136685237513628484410146475880276899689323468288129178652504797093820419402611691354199968499448738482587415636727937353639264845197813295922091561637504736126720760129127710879063043647425297778439069116811334073539456451043564046959839163407469915211595468718792531664679340442279513006653831781499155674396529973036072198720572542914738630057353297633085013244779323578115668031532144051510758240504037804690564298890171218568053886450388507561335540224075309922339483204122333658701871584147135738144358394867585372134490396264937274938848938884293776466212293402264641368524174512841804801230279990820989956713963566987970818315606031084417487965298373510594915942429581446481759482857537804431542098380533075194397625795605337047384493682506827547173206735463795863376044170821429161475172513429888642402089329334654087406739184258619435041737233405001461505889892578125e-1644")
      &&  check(convert(0xcccaaacccaaacccaULL, 0xaacccaaacccaaaccULL),
                "-124514581107511552210796456934966803687304842980295573828954497922493752983397188814711304411560018580965744046315133789985274208017368151964100284400784216106649187287727268989948309893335776137201236307422254490384994342132786695251856340822607539332337741185911979986209464222776112117543477310592395735321641016191765613924234896253051931334188353106422231052895112533426462965071195000083346118845388851222468275853899619767858364593491745895616655921022591572983370616010095670881627966440183912948095715866505356803258659518882310562527709556367822539262111581385341941163873435919341717170180065638145777392282815973491833042960716493005101610346003273833563515742996380936304245423639950200211170835546053201980835724318930743625600269679260909350277600256315069013053332133830043213033329696436217829598890872375814523266366034383531514035947792389939922899745714167418517458817088636450662300503353562047987996978943856662174717195437379600755109302771921946748859230686543872")
      &&  check(convert(0x0000000000000000ULL, 0x0000000000000001ULL),
                "x")
      &&  check(convert(0x8000000000000000ULL, 0x0000000000000001ULL),
                "y")
)
    exit(0);
  else
    exit(1);
}

#elif CXX_LONG_DOUBLE_BINARY_FORMAT == PPL_FLOAT_INTEL_DOUBLE_EXTENDED

int
main() {
  if (check(convert(0xaaacccaaacccaaacULL, 0xccaaacccaaacccaaULL),
            "-7.6048540943660203383375998875878002021755137452856942966991187375790618225432711954682137529456970686263412309600617913197560145993931792374946076061175594550915924955313391528566777352996816141138550473090399783817652516896553304678788796532976847530386107750759127004897950996937530751872097675156395937218234460013748219954603465088115161828048215763754331575034447236689765045674584188927116128770082933362914567237187017530082528540058002631800274192146485961758366625476271676375489358478966148719270989233284454992652229565352739884432045036085427546783826745250197623257802129011015273728848161395367551745780868250488191368846207890422268873532651627591649389757751752362072212699309947970918940313250863861141479770240104635553035870698789854752554391365757900620463269938427975381635241159694500569550818398323639621243086116154792038064941523448921284117826015673798399008555604372098051095571652170081985843614541956756469168604624857938653843172027861680499952062356914208628014745759010068414302636374017506453133466034362025545080555878082849488386388633197121003201192243150535143329731394874806398663589117246866205872431804204733617792317769570293754056793574570217834482046448788177551912250351735294891953434051815332631157674735614138641122106756749236824504094008852401427746414294902929999820878756040223246586814590339767277305131757114819123212897500810087015748205562614251410818122967399030151040544000563841334553718469935435435467196184665715776274355094471974036803615388313095637066824428688301387559074204015990782977635088047810891072724763113879034313256582868462323549141603475107584159170279311985555035822254439699354641467841523895459190280971487264907972306090449968125859834702627544039374770757804202780369083049631377117943503836158566134919890165392965694050010089785271180956974707841066789578714463804030217977213138932711313311673101336981407798868338574571646697479192174043005729926344062133712267722538847635563454980776602355539986984320762864338177037919835721981686778834558429264194379257521818498431326991615024245632036376472844033831041082865649867453234086495085785897620758602105639344460383483879837994732204331335249564434458633345708439547881275060781028856140511029543559841701048277393119691261302356763314623124427357421753631218361407626116820986377721964654181839884670481278855478057996766639496909094607181503284084821580817995489740980323820218685313435967428474842973086612053963343516426226771094376179468881265734324847319127862733279299033951360912038720313525324094079916937921290391173035983474894312808532257620563284126400481460163180987618432784215807933623038747129658746767737999870125917269554155887740155308886259497202672935871853706835670467770080598813171256855182510726902033818328368569915805303784312301890212694874227119220544172084552511408717615136830401766455214293141216171050374325461714383991698910564587610624980490526840861990674615172112493813749497898151186927777122955666180439323595468816129418014664347852590958362752922841159054568358354108159485566264221008508127941168192513144760720303715640604755054290633421601734103622748053919536319416025380484868142967373186019970714662893713233834399238357795019603619284595839414945178963942707310299674873908104634979966232181071013259653467885733418936194081202149071958107062125873498848807502257018093517304220495114497635240876547262237411350327960679115197531609627900227913193653254580253539005743563270152329126178570329413401577715075363838562221558204219798925982825556469998988615897432425107152113543617151738802778259560442930074253918797315241708532198010528564246933829811859278710445896556638416265987381678070434371355795025956293319362293063591248665429733880825207421011852020394068840244110140622151494488609575671090387230241296949998536132398625008053543954239573998167556201366323875845409929752349853515625e-1644")
      && check(convert(0xcccaaacccaaacccaULL, 0xaacccaaacccaaaccULL),
               "-99658331877181425640389193712445288804009112642407197633229907048864350192381814628233384153539524368748305269642704450459572458913058829202094408933558533552137589226430537671503754737153845553845646099179512540696038707395491223325946106007770844660381340028079827237033670900446083793353682761885084154898636897779677124010119288945740273072415898996441722571487815052387317025675191665761918119006431828756780493604546658949166486641354783002536071366287780290680620995991797712341457334946893188786269086688063732222194404683551757689083590842400866213237312413463207537587813396338061744078437770542720749055069473347142994267706326342325536219464867910547533482061181116137767384001927599515332824741827726661184966512254203502805790565338206862173475388342339711722457620964017690492860707751327158273522191943184085888284707357024653025991470473697475045491586713324994056478341556198451786713470909185879382607340766256394396819602885198511409676789226542867632933493115191296")
      &&  check(convert(0x0000000000000000ULL, 0x0000000000000001ULL),
                "3.645199531882474602528405933619419816399050815693563343720980487028371688633397736809560708625827205197247347347203531101966985632622032169973508075589809005483822581177931678569225263805633559756621562565983410728940319793553527268591240799954172811015518538383046054768715422449295305859718268214262622067532355460844068079259753739688226338971902813354664211957293812000216762672292032277433639030845605529795518855299212255321171163487629138462930035513852750160313284578587346566858083349053123705193988703983308587839946322501468602459466376586870456423634710242397194658860357568067134477982764219736292817751295560536845761267846647908517463250923736039512722781415953366096399444403402117053488448021977763604437908687623249034116909294550532283554604255016471048510990155249694820376175072774521597924829264164672829379224834378522148847524461653340453140898534938901079999466084995792940867082225167898092626332284133633537230365710606672711016101696986908545526816093446785575823545286456670464909287063062587561930219192839574686079732400741932670792586584247903252601714502511652018733705556477669856403061671860988301022089008752404238293812121415758527179547281628232710885994458574715033852877595426024800791719981955344151916599003503828822200355665967958771090937688409231050763744882094456320484272716122798149836361660589595209083576887254232532955229749892640550762959438241278496193819382077545905461172547961340469817691165676094261320725727312607482937653140421619686103059529199421431937449566099337396063075218302243845475341677972462038126626903408167086517545386382155008956065955410392914952623927880847159533184535486666480480563407531428385329300522477684217050951264747454635754866214784941542315111038630684391425212439304190584122374222972284606537485052464648655369719099026760518287560996997210778473066980129427427439517032390964791367678221749630975419713438139162678878555999177528450882748046538588177447270306738234898502976902853001364550405227287093940058325788585457368654991956265863050083472087623066020903378919489920975190829421602010382039477772083400661519154972695436582305021910908576692048173534958894170976763084807837402813849227540942073315401115262334876815962087441302256558438912500607230205782013083674113023497612445214795170983848687988348203289441256908755565216081815151205638893112562415329084456934095146184469290901166110634875590164835606941629407489774379792739804674764243483912084691871769225446506284310565309190872477286255925383528545036360550854226919571246361133225904820301916588317084377712259367894846411294822587075835486985645510829880528578782698412556249274522235061092454342386202327120407827540333914613192189174315884136688019435966273663470431440443032136411775605030601436837063972690330417475187330200911967500496761618122614796452937124070398703890868915527051490465736745397764941094879479649438162576614346948652085308024696358256756585794568493319042053882843808180358787110774418075478801186519577416271896383169835708225636584654568643702618602433548938163720732772538345454513065011540675765510656970500413537205370067924880209217363407323673368448004904408413977741706965494247040799786451861822188473571257556819433284087486023676249467869483631380473856486239547015603318322612783652068699798539400406637311682731115340677841660240710431551140370410375585572939303084073843540702120551963050514959945741359169911676575478403279380112020347348292538150798320452794842427526501796852911863108178276638472320237870082862271763396195139513712303136194366021540830531456910584048372546025177765140460207112923151923176402146752868221966889915381596481253160696822260723194259521813054303457222367967929268763072892355278854714278243863110783067060124459039315528176840304931522813148745824350892130595015198002557204332483215551447097512510076223364801202888087635650654634946887232727623906459076670227108634162319210357007273369354657187569046394884895083794103531835959613994575377897775525461977464747518162975010091463561925032742645594645800581600698347817023194379921397347681150492687237349021564206463096138703201250277757980410772647014391579144424375252519766764670458008515297647624144814453496069685127439800629552075692648608681506879044376428977463175175205181547958459515159074701285838493694034007662410100183533141516684185460758175066481561018901133031951042099053297118837448984443230856642737606478787880285299903521855025612413471034466624171559209077538498475106811294029060334271803320566493935024621719717684804443351866946690525266060758332190531807232565501890293754259590947433140384335366973398816899253698302119916142891631005349335372158005779944529176735887193980409288474621694590303098552382376969442365186023130985507823617670051191889015351479659778676132449671642015059540438237303922903056079068344635440276772565425944329927654906262952475555750912023879424636021462043321631428365675851865654901693474343411406220907550090045689588323936814675126103464401223728058185048320475251266882875299120582253090033177883674432343812734123922042926554908548231473285349572210962289889800994026533629321464700552029391517293055196218065667251276237490129206098414338903210942488902792253924667941082273267563528653863343443486495762400409978995985052082310730277076965242846278402568285187365588876653245423047205943478612931964211293489374119565751486787204884502307512372923973119191125614068756094526892783321688030310900558025683455451898487401139315290743477461921025987905332236299398859448938742087487316288730711068752763449392366897236258997091176996253284306687635454361862179407191652155243650619571720232128624130785404930566805029233271375546253313287446285812219961565022654510373870581648214791139170870970509074158721967633425471550515801498191107216277620692347014234913527385812164834475002007099402122991439542783981984927181300669603290190495106195784248531299740262706106798338573523977365240941293695214188675632715447081372252551022981921251125675131839210074132286029621443262127145872022404314258219255606415280218445074654034790115075558513374422753617188198385931164810182817002794172279803028202086567081267453349341345496389239379776494419022301042067986600501045466950004057134726934147691678031986698845370299987067384407310337433828116514830745374490760171672152978595040351405572526523026051215093709900567873568385242574546385008567738263951532676549294356417565797771595638496719149577804216291892125541055147173723744991756669672459021375111288754125372918394417976243093028214703329386031799313949535161343892720409046065009958980978947997662545514664194262097665297242612367968766000629174655887090824363583653843658980277566031286429628476318572915045823895805826010132712977834418613468288832988547377174550796802573148684253294172285056777826927377158058647145403557721233512002495437339413998842782599710186215723437958154275340509811072349041046483806284608873394275718878590418692809288333423522781240698974441829879303794241455852776713321354870647251094720675572322788447908778778892116234131617608416732280987493141331884927860259324392781255786150891859203497212615916404999097067778739914857961305884934678762043515521190581898256624635957830927811421154992139986999936203631149852372802564314896151749326404428772008250428569338329698161850171265411426708113723558325059062871506712838460986031147060351491506316012532538793354499545667009527573810892048004652452452139688789392912938251888341298122235232861138733903153560967292104241190946350516769769305030762386908399592555043192236069279491224465826684203312081255431851756341234566913972589390601558650830437402045595207689996159597545711808203688318112918947661662115802919578636403430323041610018063696707221249826383715263388850307418469423973486747009233945036220901518185766942733836846126816638158345048782728241251279820310193223512959111029884002230571688216854282257873218631744450950552327428952538149545262779889824399028513132208638633070602135522752076661567872472325125674291268881849101416382703647451428232847993332157180794015036365361645888146355749366150209085457189187232786399585879941680370348141105404742298452497895369287193974496140445677301271403589665822911096832952021181343571136957607816318342755770560406569920261633966403484121679869542684843686908354373688437968683525723666121485947946747887572716360800696442816474113593466106089204179554677145374582437962664618883018628687510079511252556002241788346284019750863992283906513572325918053464080643521532154825074820239077990779007069588034029619562190416747359712884084324521598678178890186409451480686781733176824920276835002477523486093586963733155424491897575495851549527034538337694314953057164019215026670773910997443279760005290641511584707193226351271670439775141076552632736166117611394934325673743882365518318561208941552931629125136799711574578916741023587251428998946963182411650554404206416336487418656105333038545773960190949602850096208569085230228708894874577523512558281973392961263921656163963369388411763476388625952406901518273413037068643383550282962237729195901788599392876651086599849223994259145259240479384380657803498058719062529007339428316229997756899857712116922758683071707472935574499244978419788171338468471751125303860911589289400806637202920429489919870263415951660888975434827304297451362325052693482001524843171229078467910537913138115458626612024970730899515114301915281613929239329351501049859225274564107846818112938339161308943153205117651716380468462296193882444293370484368530096898812778973178284912798550245246063411918482638261694029245273291646707331594675213428158755273882438357960245064051015888918541801139771619743221405037797285669481455810653320008904215997597975907391512026214020012010134707536774227636477580918167507850485197065326391091171451763751237612739498468510009055480025096015985581769370179656781151306565952590101977398335185042637681982306448413722177895665290302796223004198526079143104070007874540548221582347389579e-4951")
      && check(convert(0x8000000000000000ULL, 0x0000000000000001ULL),
               "3.645199531882474602528405933619419816399050815693563343720980487028371688633397736809560708625827205197247347347203531101966985632622032169973508075589809005483822581177931678569225263805633559756621562565983410728940319793553527268591240799954172811015518538383046054768715422449295305859718268214262622067532355460844068079259753739688226338971902813354664211957293812000216762672292032277433639030845605529795518855299212255321171163487629138462930035513852750160313284578587346566858083349053123705193988703983308587839946322501468602459466376586870456423634710242397194658860357568067134477982764219736292817751295560536845761267846647908517463250923736039512722781415953366096399444403402117053488448021977763604437908687623249034116909294550532283554604255016471048510990155249694820376175072774521597924829264164672829379224834378522148847524461653340453140898534938901079999466084995792940867082225167898092626332284133633537230365710606672711016101696986908545526816093446785575823545286456670464909287063062587561930219192839574686079732400741932670792586584247903252601714502511652018733705556477669856403061671860988301022089008752404238293812121415758527179547281628232710885994458574715033852877595426024800791719981955344151916599003503828822200355665967958771090937688409231050763744882094456320484272716122798149836361660589595209083576887254232532955229749892640550762959438241278496193819382077545905461172547961340469817691165676094261320725727312607482937653140421619686103059529199421431937449566099337396063075218302243845475341677972462038126626903408167086517545386382155008956065955410392914952623927880847159533184535486666480480563407531428385329300522477684217050951264747454635754866214784941542315111038630684391425212439304190584122374222972284606537485052464648655369719099026760518287560996997210778473066980129427427439517032390964791367678221749630975419713438139162678878555999177528450882748046538588177447270306738234898502976902853001364550405227287093940058325788585457368654991956265863050083472087623066020903378919489920975190829421602010382039477772083400661519154972695436582305021910908576692048173534958894170976763084807837402813849227540942073315401115262334876815962087441302256558438912500607230205782013083674113023497612445214795170983848687988348203289441256908755565216081815151205638893112562415329084456934095146184469290901166110634875590164835606941629407489774379792739804674764243483912084691871769225446506284310565309190872477286255925383528545036360550854226919571246361133225904820301916588317084377712259367894846411294822587075835486985645510829880528578782698412556249274522235061092454342386202327120407827540333914613192189174315884136688019435966273663470431440443032136411775605030601436837063972690330417475187330200911967500496761618122614796452937124070398703890868915527051490465736745397764941094879479649438162576614346948652085308024696358256756585794568493319042053882843808180358787110774418075478801186519577416271896383169835708225636584654568643702618602433548938163720732772538345454513065011540675765510656970500413537205370067924880209217363407323673368448004904408413977741706965494247040799786451861822188473571257556819433284087486023676249467869483631380473856486239547015603318322612783652068699798539400406637311682731115340677841660240710431551140370410375585572939303084073843540702120551963050514959945741359169911676575478403279380112020347348292538150798320452794842427526501796852911863108178276638472320237870082862271763396195139513712303136194366021540830531456910584048372546025177765140460207112923151923176402146752868221966889915381596481253160696822260723194259521813054303457222367967929268763072892355278854714278243863110783067060124459039315528176840304931522813148745824350892130595015198002557204332483215551447097512510076223364801202888087635650654634946887232727623906459076670227108634162319210357007273369354657187569046394884895083794103531835959613994575377897775525461977464747518162975010091463561925032742645594645800581600698347817023194379921397347681150492687237349021564206463096138703201250277757980410772647014391579144424375252519766764670458008515297647624144814453496069685127439800629552075692648608681506879044376428977463175175205181547958459515159074701285838493694034007662410100183533141516684185460758175066481561018901133031951042099053297118837448984443230856642737606478787880285299903521855025612413471034466624171559209077538498475106811294029060334271803320566493935024621719717684804443351866946690525266060758332190531807232565501890293754259590947433140384335366973398816899253698302119916142891631005349335372158005779944529176735887193980409288474621694590303098552382376969442365186023130985507823617670051191889015351479659778676132449671642015059540438237303922903056079068344635440276772565425944329927654906262952475555750912023879424636021462043321631428365675851865654901693474343411406220907550090045689588323936814675126103464401223728058185048320475251266882875299120582253090033177883674432343812734123922042926554908548231473285349572210962289889800994026533629321464700552029391517293055196218065667251276237490129206098414338903210942488902792253924667941082273267563528653863343443486495762400409978995985052082310730277076965242846278402568285187365588876653245423047205943478612931964211293489374119565751486787204884502307512372923973119191125614068756094526892783321688030310900558025683455451898487401139315290743477461921025987905332236299398859448938742087487316288730711068752763449392366897236258997091176996253284306687635454361862179407191652155243650619571720232128624130785404930566805029233271375546253313287446285812219961565022654510373870581648214791139170870970509074158721967633425471550515801498191107216277620692347014234913527385812164834475002007099402122991439542783981984927181300669603290190495106195784248531299740262706106798338573523977365240941293695214188675632715447081372252551022981921251125675131839210074132286029621443262127145872022404314258219255606415280218445074654034790115075558513374422753617188198385931164810182817002794172279803028202086567081267453349341345496389239379776494419022301042067986600501045466950004057134726934147691678031986698845370299987067384407310337433828116514830745374490760171672152978595040351405572526523026051215093709900567873568385242574546385008567738263951532676549294356417565797771595638496719149577804216291892125541055147173723744991756669672459021375111288754125372918394417976243093028214703329386031799313949535161343892720409046065009958980978947997662545514664194262097665297242612367968766000629174655887090824363583653843658980277566031286429628476318572915045823895805826010132712977834418613468288832988547377174550796802573148684253294172285056777826927377158058647145403557721233512002495437339413998842782599710186215723437958154275340509811072349041046483806284608873394275718878590418692809288333423522781240698974441829879303794241455852776713321354870647251094720675572322788447908778778892116234131617608416732280987493141331884927860259324392781255786150891859203497212615916404999097067778739914857961305884934678762043515521190581898256624635957830927811421154992139986999936203631149852372802564314896151749326404428772008250428569338329698161850171265411426708113723558325059062871506712838460986031147060351491506316012532538793354499545667009527573810892048004652452452139688789392912938251888341298122235232861138733903153560967292104241190946350516769769305030762386908399592555043192236069279491224465826684203312081255431851756341234566913972589390601558650830437402045595207689996159597545711808203688318112918947661662115802919578636403430323041610018063696707221249826383715263388850307418469423973486747009233945036220901518185766942733836846126816638158345048782728241251279820310193223512959111029884002230571688216854282257873218631744450950552327428952538149545262779889824399028513132208638633070602135522752076661567872472325125674291268881849101416382703647451428232847993332157180794015036365361645888146355749366150209085457189187232786399585879941680370348141105404742298452497895369287193974496140445677301271403589665822911096832952021181343571136957607816318342755770560406569920261633966403484121679869542684843686908354373688437968683525723666121485947946747887572716360800696442816474113593466106089204179554677145374582437962664618883018628687510079511252556002241788346284019750863992283906513572325918053464080643521532154825074820239077990779007069588034029619562190416747359712884084324521598678178890186409451480686781733176824920276835002477523486093586963733155424491897575495851549527034538337694314953057164019215026670773910997443279760005290641511584707193226351271670439775141076552632736166117611394934325673743882365518318561208941552931629125136799711574578916741023587251428998946963182411650554404206416336487418656105333038545773960190949602850096208569085230228708894874577523512558281973392961263921656163963369388411763476388625952406901518273413037068643383550282962237729195901788599392876651086599849223994259145259240479384380657803498058719062529007339428316229997756899857712116922758683071707472935574499244978419788171338468471751125303860911589289400806637202920429489919870263415951660888975434827304297451362325052693482001524843171229078467910537913138115458626612024970730899515114301915281613929239329351501049859225274564107846818112938339161308943153205117651716380468462296193882444293370484368530096898812778973178284912798550245246063411918482638261694029245273291646707331594675213428158755273882438357960245064051015888918541801139771619743221405037797285669481455810653320008904215997597975907391512026214020012010134707536774227636477580918167507850485197065326391091171451763751237612739498468510009055480025096015985581769370179656781151306565952590101977398335185042637681982306448413722177895665290302796223004198526079143104070007874540548221582347389579e-4951"))
    exit(0);
  else
    exit(1);
}

#else // CXX_LONG_DOUBLE_BINARY_FORMAT != FLOAT_INTEL_DOUBLE_EXTENDED

int
main() {
  exit(1);
}

#endif // CXX_LONG_DOUBLE_BINARY_FORMAT != FLOAT_INTEL_DOUBLE_EXTENDED

#elif SIZEOF_LONG_DOUBLE == 8

double
convert(uint32_t msp, uint32_t lsp) {
  union {
    long double value;
    struct {
#ifdef WORDS_BIGENDIAN
      uint32_t msp;
      uint32_t lsp;
#else
      uint32_t lsp;
      uint32_t msp;
#endif
    } parts;
  } u;

  u.parts.msp = msp;
  u.parts.lsp = lsp;
  return u.value;
}

#if CXX_LONG_DOUBLE_BINARY_FORMAT == PPL_FLOAT_IEEE754_DOUBLE

int
main() {
  if (check(convert(0xaaacccaaUL, 0xacccaaacUL),
            "-4.018242396032647085467373664662028399901175154542925376476863248797653889888945947404163925979898721593782464256360719269163883854613473748830842329884157359816532025640075051481726120707111709993717456369512975427023957197464411926714771905463723621065863511603311053477227687835693359375e-103")
      && check(convert(0xcccaaaccUL, 0xcaaacccaUL),
               "-85705035845709846787631445265530356117787053916987832397725696")
      && check(convert(0x00000000UL, 0x00000001UL),
               "4.940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954457177309266567103559397963987747960107818781263007131903114045278458171678489821036887186360569987307230500063874091535649843873124733972731696151400317153853980741262385655911710266585566867681870395603106249319452715914924553293054565444011274801297099995419319894090804165633245247571478690147267801593552386115501348035264934720193790268107107491703332226844753335720832431936092382893458368060106011506169809753078342277318329247904982524730776375927247874656084778203734469699533647017972677717585125660551199131504891101451037862738167250955837389733598993664809941164205702637090279242767544565229087538682506419718265533447265625e-324")
      && check(convert(0x80000000UL, 0x00000001UL),
               "-4.940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954457177309266567103559397963987747960107818781263007131903114045278458171678489821036887186360569987307230500063874091535649843873124733972731696151400317153853980741262385655911710266585566867681870395603106249319452715914924553293054565444011274801297099995419319894090804165633245247571478690147267801593552386115501348035264934720193790268107107491703332226844753335720832431936092382893458368060106011506169809753078342277318329247904982524730776375927247874656084778203734469699533647017972677717585125660551199131504891101451037862738167250955837389733598993664809941164205702637090279242767544565229087538682506419718265533447265625e-324"))
    exit(0);
  else
    exit(1);
}

#else // CXX_LONG_DOUBLE_BINARY_FORMAT != FLOAT_IEEE754_DOUBLE

int
main() {
  exit(1);
}

#endif // CXX_LONG_DOUBLE_BINARY_FORMAT != FLOAT_IEEE754_DOUBLE

#else // SIZEOF_LONG_DOUBLE != 8

int
main() {
  exit(1);
}

#endif // SIZEOF_LONG_DOUBLE != 8
]])],
  AC_MSG_RESULT(yes)
  ac_cxx_long_double_exact_output=1,
  AC_MSG_RESULT(no)
  ac_cxx_long_double_exact_output=0)

AC_DEFINE_UNQUOTED(CXX_LONG_DOUBLE_EXACT_OUTPUT, $ac_cxx_long_double_exact_output,
  [Not zero if C++ supports exact output for long doubles.])

AC_LANG_POP(C++)
CPPFLAGS="$ac_save_CPPFLAGS"
LIBS="$ac_save_LIBS"
])
