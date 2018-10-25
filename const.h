//
// Created by tufen on 2018/10/23.
//

#ifndef MMSE_CONST_H
#define MMSE_CONST_H

#define EPSILON 0.000001F

// Domain: 0.001 ~ 0.5
static float ExpintTable1[500] = {6.33153936413615F, 5.63939143396494F, 5.23492507691165F, 4.94824125651360F, 4.72609545858444F, 4.54477115683906F, 4.39161723405586F, 4.25908210080260F, 4.14229482717614F, 4.03792957653811F, 3.94361416507444F, 3.85759706007702F, 3.77854812837773F, 3.70543343651052F, 3.63743334995231F, 3.57388711871546F, 3.51425429210118F, 3.45808717909408F, 3.40501076461633F, 3.35470778330971F, 3.30690743883812F, 3.26137674984624F, 3.21791382119158F, 3.17634254828989F, 3.13650840321517F, 3.09827504776313F, 3.06152158606426F, 3.02614031708686F, 2.99203488170511F, 2.95911872402128F, 2.92731380507851F, 2.89654952085833F, 2.86676178682571F, 2.83789225917520F, 2.80988766899124F, 2.78269925022877F, 2.75628224608441F, 2.73059548120986F, 2.70560098950218F, 2.68126368902528F, 2.65755109707773F, 2.63443307960029F, 2.61188163007365F, 2.58987067383731F, 2.56837589440108F, 2.54737457884799F, 2.52684547986474F, 2.50676869229857F, 2.48712554244313F, 2.46789848850997F, 2.44907103095643F, 2.43062763152119F, 2.41255363997231F, 2.39483522770240F, 2.37745932741712F, 2.36041357825803F, 2.34368627578265F, 2.32726632629475F, 2.31114320507867F, 2.29530691814378F, 2.27974796713116F, 2.26445731707363F, 2.24942636673543F, 2.23464692128761F, 2.22011116710190F, 2.20581164846892F, 2.19174124606712F, 2.17789315702680F, 2.16426087644945F, 2.15083818025680F, 2.13761910925637F, 2.12459795432145F, 2.11176924259316F, 2.09912772462139F, 2.08666836236871F, 2.07438631800884F, 2.06227694345737F, 2.05033577057783F, 2.03855850201183F, 2.02694100258574F, 2.01547929125139F, 2.00416953352107F, 1.99300803436109F, 1.98199123151100F, 1.97111568919802F, 1.96037809221915F, 1.94977524036537F, 1.93930404316446F, 1.92896151492086F, 1.91874477003266F, 1.90865101856733F, 1.89867756207924F, 1.88882178965323F, 1.87908117415985F, 1.86945326870865F, 1.85993570328723F, 1.85052618157445F, 1.84122247791703F, 1.83202243445968F, 1.82292395841939F, 1.81392501949540F, 1.80502364740671F, 1.79621792954979F, 1.78750600876935F, 1.77888608123583F, 1.77035639442354F, 1.76191524518360F, 1.75356097790666F, 1.74529198277014F, 1.73710669406567F, 1.72900358860208F, 1.72098118418005F, 1.71303803813460F, 1.70517274594176F, 1.69738393988603F, 1.68967028778564F, 1.68203049177242F, 1.67446328712364F, 1.66696744114317F, 1.65954175208938F, 1.65218504814758F, 1.64489618644475F, 1.63767405210444F, 1.63051755734000F, 1.62342564058417F, 1.61639726565340F, 1.60943142094514F, 1.60252711866667F, 1.59568339409389F, 1.58889930485880F, 1.58217393026415F, 1.57550637062431F, 1.56889574663089F, 1.56234119874219F, 1.55584188659529F, 1.54939698843990F, 1.54300570059289F, 1.53666723691273F, 1.53038082829278F, 1.52414572217289F, 1.51796118206826F, 1.51182648711501F, 1.50574093163171F, 1.49970382469613F, 1.49371448973666F, 1.48777226413783F, 1.48187649885916F, 1.47602655806709F, 1.47022181877919F, 1.46446167052028F, 1.45874551499005F, 1.45307276574158F, 1.44744284787039F, 1.44185519771371F, 1.43630926255935F, 1.43080450036407F, 1.42534037948083F, 1.41991637839478F, 1.41453198546754F, 1.40918669868949F, 1.40388002543983F, 1.39861148225397F, 1.39338059459819F, 1.38818689665114F, 1.38302993109194F, 1.37790924889475F, 1.37282440912947F, 1.36777497876843F, 1.36276053249873F, 1.35778065254024F, 1.35283492846881F, 1.34792295704476F, 1.34304434204620F, 1.33819869410729F, 1.33338563056104F, 1.32860477528666F, 1.32385575856114F, 1.31913821691513F, 1.31445179299275F, 1.30979613541537F, 1.30517089864914F, 1.30057574287617F, 1.29601033386927F, 1.29147434287001F, 1.28696744647023F, 1.28248932649660F, 1.27803966989839F, 1.27361816863814F, 1.26922451958530F, 1.26485842441262F, 1.26051958949533F, 1.25620772581287F, 1.25192254885323F, 1.24766377851975F, 1.24343113904031F, 1.23922435887882F, 1.23504317064902F, 1.23088731103039F, 1.22675652068626F, 1.22265054418389F, 1.21856912991660F, 1.21451203002782F, 1.21047900033696F, 1.20646980026724F, 1.20248419277510F, 1.19852194428150F, 1.19458282460475F, 1.19066660689505F, 1.18677306757053F, 1.18290198625489F, 1.17905314571646F, 1.17522633180872F, 1.17142133341224F, 1.16763794237793F, 1.16387595347169F, 1.16013516432024F, 1.15641537535834F, 1.15271638977706F, 1.14903801347337F, 1.14538005500082F, 1.14174232552131F, 1.13812463875802F, 1.13452681094936F, 1.13094866080393F, 1.12739000945649F, 1.12385068042499F, 1.12033049956838F, 1.11682929504554F, 1.11334689727494F, 1.10988313889530F, 1.10643785472705F, 1.10301088173459F, 1.09960205898947F, 1.09621122763424F, 1.09283823084711F, 1.08948291380742F, 1.08614512366176F, 1.08282470949081F, 1.07952152227697F, 1.07623541487250F, 1.07296624196851F, 1.06971386006443F, 1.06647812743823F, 1.06325890411715F, 1.06005605184912F, 1.05686943407471F, 1.05369891589963F, 1.05054436406786F, 1.04740564693527F, 1.04428263444374F, 1.04117519809585F, 1.03808321093007F, 1.03500654749642F, 1.03194508383258F, 1.02889869744056F, 1.02586726726374F, 1.02285067366439F, 1.01984879840164F, 1.01686152460984F, 1.01388873677738F, 1.01093032072589F, 1.00798616358984F, 1.00505615379652F, 1.00214018104644F, 0.999238136294059F, 0.996349911728865F, 0.993475400756876F, 0.990614497982423F, 0.987767099190299F, 0.984933101328234F, 0.982112402489699F, 0.979304901897022F, 0.976510499884809F, 0.973729097883682F, 0.970960598404302F, 0.968204905021682F, 0.965461922359790F, 0.962731556076425F, 0.960013712848367F, 0.957308300356788F, 0.954615227272931F, 0.951934403244034F, 0.949265738879512F, 0.946609145737375F, 0.943964536310890F, 0.941331824015476F, 0.938710923175825F, 0.936101749013249F, 0.933504217633244F, 0.930918246013275F, 0.928343751990763F, 0.925780654251284F, 0.923228872316966F, 0.920688326535087F, 0.918158938066864F, 0.915640628876432F, 0.913133321720014F, 0.910636940135260F, 0.908151408430781F, 0.905676651675847F, 0.903212595690257F, 0.900759167034383F, 0.898316292999373F, 0.895883901597516F, 0.893461921552770F, 0.891050282291436F, 0.888648913932996F, 0.886257747281089F, 0.883876713814638F, 0.881505745679123F, 0.879144775677990F, 0.876793737264197F, 0.874452564531905F, 0.872121192208285F, 0.869799555645474F, 0.867487590812641F, 0.865185234288193F, 0.862892423252093F, 0.860609095478304F, 0.858335189327350F, 0.856070643738996F, 0.853815398225033F, 0.851569392862186F, 0.849332568285124F, 0.847104865679583F, 0.844886226775585F, 0.842676593840777F, 0.840475909673856F, 0.838284117598100F, 0.836101161455002F, 0.833926985597995F, 0.831761534886266F, 0.829604754678678F, 0.827456590827773F, 0.825316989673861F, 0.823185898039208F, 0.821063263222303F, 0.818949032992211F, 0.816843155583011F, 0.814745579688315F, 0.812656254455868F, 0.810575129482225F, 0.808502154807510F, 0.806437280910244F, 0.804380458702259F, 0.802331639523674F, 0.800290775137951F, 0.798257817727021F, 0.796232719886476F, 0.794215434620836F, 0.792205915338876F, 0.790204115849027F, 0.788209990354839F, 0.786223493450506F, 0.784244580116458F, 0.782273205715011F, 0.780309325986082F, 0.778352897042962F, 0.776403875368148F, 0.774462217809232F, 0.772527881574849F, 0.770600824230679F, 0.768681003695509F, 0.766768378237340F, 0.764862906469556F, 0.762964547347142F, 0.761073260162954F, 0.759189004544038F, 0.757311740448002F, 0.755441428159437F, 0.753578028286381F, 0.751721501756837F, 0.749871809815336F, 0.748028914019544F, 0.746192776236916F, 0.744363358641393F, 0.742540623710147F, 0.740724534220363F, 0.738915053246067F, 0.737112144154998F, 0.735315770605516F, 0.733525896543553F, 0.731742486199606F, 0.729965504085765F, 0.728194914992784F, 0.726430683987183F, 0.724672776408401F, 0.722921157865967F, 0.721175794236724F, 0.719436651662080F, 0.717703696545296F, 0.715976895548810F, 0.714256215591593F, 0.712541623846539F, 0.710833087737889F, 0.709130574938690F, 0.707434053368279F, 0.705743491189805F, 0.704058856807781F, 0.702380118865662F, 0.700707246243463F, 0.699040208055393F, 0.697378973647534F, 0.695723512595532F, 0.694073794702333F, 0.692429789995936F, 0.690791468727175F, 0.689158801367534F, 0.687531758606980F, 0.685910311351833F, 0.684294430722649F, 0.682684088052144F, 0.681079254883129F, 0.679479902966478F, 0.677886004259118F, 0.676297530922046F, 0.674714455318365F, 0.673136750011346F, 0.671564387762516F, 0.669997341529763F, 0.668435584465468F, 0.666879089914658F, 0.665327831413178F, 0.663781782685891F, 0.662240917644895F, 0.660705210387756F, 0.659174635195774F, 0.657649166532257F, 0.656128779040825F, 0.654613447543725F, 0.653103147040173F, 0.651597852704708F, 0.650097539885575F, 0.648602184103115F, 0.647111761048182F, 0.645626246580576F, 0.644145616727490F, 0.642669847681983F, 0.641198915801459F, 0.639732797606177F, 0.638271469777766F, 0.636814909157763F, 0.635363092746164F, 0.633915997699998F, 0.632473601331907F, 0.631035881108752F, 0.629602814650226F, 0.628174379727492F, 0.626750554261822F, 0.625331316323269F, 0.623916644129338F, 0.622506516043683F, 0.621100910574808F, 0.619699806374795F, 0.618303182238032F, 0.616911017099967F, 0.615523290035870F, 0.614139980259605F, 0.612761067122424F, 0.611386530111769F, 0.610016348850085F, 0.608650503093652F, 0.607288972731423F, 0.605931737783878F, 0.604578778401895F, 0.603230074865621F, 0.601885607583366F, 0.600545357090505F, 0.599209304048392F, 0.597877429243282F, 0.596549713585273F, 0.595226138107252F, 0.593906683963851F, 0.592591332430423F, 0.591280064902018F, 0.589972862892376F, 0.588669708032933F, 0.587370582071829F, 0.586075466872932F, 0.584784344414874F, 0.583497196790091F, 0.582214006203880F, 0.580934754973459F, 0.579659425527039F, 0.578388000402911F, 0.577120462248533F, 0.575856793819634F, 0.574596977979323F, 0.573340997697209F, 0.572088836048530F, 0.570840476213289F, 0.569595901475400F, 0.568355095221847F, 0.567118040941839F, 0.565884722225992F, 0.564655122765501F, 0.563429226351332F, 0.562207016873418F, 0.560988478319864F, 0.559773594776161F};

// Domain: 0.5 ~ 1.5
static float ExpintTable2[251] = {0.559773594776161F, 0.554950295774654F, 0.550184228566447F, 0.545474419724144F, 0.540819918846431F, 0.536219797845636F, 0.531673150262605F, 0.527179090607617F, 0.522736753726183F, 0.518345294188611F, 0.514003885702249F, 0.509711720545442F, 0.505468009022217F, 0.501271978936804F, 0.497122875087133F, 0.493019958776493F, 0.488962507342567F, 0.484949813703121F, 0.480981185917635F, 0.477055946764210F, 0.473173433331126F, 0.469332996622433F, 0.465534001177009F, 0.461775824700544F, 0.458057857709903F, 0.454379503189402F, 0.450740176258502F, 0.447139303850470F, 0.443576324401589F, 0.440050687550483F, 0.436561853847192F, 0.433109294471587F, 0.429692490960805F, 0.426310934945320F, 0.422964127893360F, 0.419651580863333F, 0.416372814263966F, 0.413127357621880F, 0.409914749356315F, 0.406734536560751F, 0.403586274791166F, 0.400469527860700F, 0.397383867640485F, 0.394328873866420F, 0.391304133951693F, 0.388309242804826F, 0.385343802653065F, 0.382407422870921F, 0.379499719813686F, 0.376620316655740F, 0.373768843233509F, 0.370944935892892F, 0.368148237341009F, 0.365378396502136F, 0.362635068377678F, 0.359917913910035F, 0.357226599850257F, 0.354560798629336F, 0.351920188233033F, 0.349304452080114F, 0.346713278903895F, 0.344146362636973F, 0.341603402299064F, 0.339084101887818F, 0.336588170272547F, 0.334115321090748F, 0.331665272647358F, 0.329237747816627F, 0.326832473946554F, 0.324449182765786F, 0.322087610292923F, 0.319747496748133F, 0.317428586467031F, 0.315130627816727F, 0.312853373114005F, 0.310596578545543F, 0.308360004090134F, 0.306143413442834F, 0.303946573940985F, 0.301769256492064F, 0.299611235503289F, 0.297472288812947F, 0.295352197623386F, 0.293250746435620F, 0.291167722985511F, 0.289102918181468F, 0.287056126043634F, 0.285027143644513F, 0.283015771050992F, 0.281021811267725F, 0.279045070181840F, 0.277085356508928F, 0.275142481740288F, 0.273216260091375F, 0.271306508451441F, 0.269413046334320F, 0.267535695830332F, 0.265674281559272F, 0.263828630624464F, 0.261998572567834F, 0.260183939326000F, 0.258384565187321F, 0.256600286749911F, 0.254830942880567F, 0.253076374674603F, 0.251336425416562F, 0.249610940541772F, 0.247899767598750F, 0.246202756212403F, 0.244519758048025F, 0.242850626776061F, 0.241195218037623F, 0.239553389410736F, 0.237925000377293F, 0.236309912290710F, 0.234707988344255F, 0.233119093540036F, 0.231543094658634F, 0.229979860229366F, 0.228429260501155F, 0.226891167414003F, 0.225365454571042F, 0.223851997211154F, 0.222350672182151F, 0.220861357914491F, 0.219383934395520F, 0.217918283144238F, 0.216464287186559F, 0.215021831031070F, 0.213590800645265F, 0.212171083432249F, 0.210762568207898F, 0.209365145178468F, 0.207978705918639F, 0.206603143349984F, 0.205238351719856F, 0.203884226580681F, 0.202540664769647F, 0.201207564388785F, 0.199884824785426F, 0.198572346533028F, 0.197270031412369F, 0.195977782393090F, 0.194695503615591F, 0.193423100373256F, 0.192160479095018F, 0.190907547328241F, 0.189664213721924F, 0.188430388010206F, 0.187205980996190F, 0.185990904536040F, 0.184785071523391F, 0.183588395874023F, 0.182400792510829F, 0.181222177349038F, 0.180052467281716F, 0.178891580165522F, 0.177739434806718F, 0.176595950947427F, 0.175461049252136F, 0.174334651294438F, 0.173216679544007F, 0.172107057353797F, 0.171005708947475F, 0.169912559407060F, 0.168827534660787F, 0.167750561471176F, 0.166681567423308F, 0.165620480913305F, 0.164567231136999F, 0.163521748078805F, 0.162483962500777F, 0.161453805931852F, 0.160431210657273F, 0.159416109708196F, 0.158408436851462F, 0.157408126579554F, 0.156415114100704F, 0.155429335329182F, 0.154450726875736F, 0.153479226038189F, 0.152514770792199F, 0.151557299782162F, 0.150606752312267F, 0.149663068337703F, 0.148726188455997F, 0.147796053898504F, 0.146872606522027F, 0.145955788800575F, 0.145045543817253F, 0.144141815256283F, 0.143244547395151F, 0.142353685096878F, 0.141469173802417F, 0.140590959523164F, 0.139718988833596F, 0.138853208864020F, 0.137993567293430F, 0.137140012342489F, 0.136292492766605F, 0.135450957849129F, 0.134615357394647F, 0.133785641722382F, 0.132961761659695F, 0.132143668535687F, 0.131331314174900F, 0.130524650891108F, 0.129723631481212F, 0.128928209219219F, 0.128138337850319F, 0.127353971585044F, 0.126575065093524F, 0.125801573499819F, 0.125033452376345F, 0.124270657738376F, 0.123513146038632F, 0.122760874161947F, 0.122013799420013F, 0.121271879546203F, 0.120535072690475F, 0.119803337414337F, 0.119076632685907F, 0.118354917875021F, 0.117638152748432F, 0.116926297465068F, 0.116219312571358F, 0.115517158996635F, 0.114819798048592F, 0.114127191408815F, 0.113439301128373F, 0.112756089623470F, 0.112077519671165F, 0.111403554405148F, 0.110734157311576F, 0.110069292224971F, 0.109408923324170F, 0.108753015128340F, 0.108101532493039F, 0.107454440606342F, 0.106811704985010F, 0.106173291470726F, 0.105539166226369F, 0.104909295732348F, 0.104283646782986F, 0.103662186482950F, 0.103044882243734F, 0.102431701780185F, 0.101822613107082F, 0.101217584535761F, 0.100616584670779F, 0.100019582406633F};

// Domain 1.5 ~ 3.5
static float ExpintTable3[126] = {0.100019582406633F, 0.0976709372158198F, 0.0953838384149070F, 0.0931564276459467F, 0.0909869129830044F, 0.0888735660844122F, 0.0868147194907422F, 0.0848087640597390F, 0.0828541465300625F, 0.0809493672062480F, 0.0790929777578066F, 0.0772835791258635F, 0.0755198195311743F, 0.0738003925777604F, 0.0721240354467908F, 0.0704895271756689F, 0.0688956870176292F, 0.0673413728774234F, 0.0658254798189725F, 0.0643469386411095F, 0.0629047145177793F, 0.0614978056992866F, 0.0601252422713888F, 0.0587860849692256F, 0.0574794240432553F, 0.0562043781745348F, 0.0549600934368431F, 0.0537457423032842F, 0.0525605226951504F, 0.0514036570709528F, 0.0502743915536392F, 0.0491719950941388F, 0.0480957586694767F, 0.0470449945137897F, 0.0460190353806841F, 0.0450172338354382F, 0.0440389615756621F, 0.0430836087790745F, 0.0421505834771471F, 0.0412393109534225F, 0.0403492331653865F, 0.0394798081888161F, 0.0386305096836003F, 0.0378008263800681F, 0.0369902615849173F, 0.0361983327058716F, 0.0354245707942568F, 0.0346685201047068F, 0.0339297376712618F, 0.0332077928991558F, 0.0325022671716214F, 0.0318127534710799F, 0.0311388560141009F, 0.0304801898995688F, 0.0298363807694920F, 0.0292070644819443F, 0.0285918867956309F, 0.0279905030656117F, 0.0274025779497217F, 0.0268277851252616F, 0.0262658070155479F, 0.0257163345259216F, 0.0251790667888503F, 0.0246537109177589F, 0.0241399817692477F, 0.0236376017133719F, 0.0231463004116726F, 0.0226658146026547F, 0.0221958878944312F, 0.0217362705642599F, 0.0212867193647089F, 0.0208469973362054F, 0.0204168736257225F, 0.0199961233113807F, 0.0195845272327421F, 0.0191818718265862F, 0.0187879489679693F, 0.0184025558163696F, 0.0180254946667384F, 0.0176565728052777F, 0.0172956023697725F, 0.0169424002143170F, 0.0165967877782784F, 0.0162585909593461F, 0.0159276399905230F, 0.0156037693209245F, 0.0152868175002407F, 0.0149766270667522F, 0.0146730444387568F, 0.0143759198093052F, 0.0140851070441270F, 0.0138004635826326F, 0.0135218503418941F, 0.0132491316235018F, 0.0129821750231990F, 0.0127208513432019F, 0.0124650345071144F, 0.0122146014773545F, 0.0119694321750053F, 0.0117294094020133F, 0.0114944187656559F, 0.0112643486052043F, 0.0110390899207104F, 0.0108185363038491F, 0.0106025838707484F, 0.0103911311967455F, 0.0101840792530053F, 0.00998133134494335F, 0.00978279305239503F, 0.00958837217147620F, 0.00939797865808188F, 0.00921152457297160F, 0.00902892402839181F, 0.00885009313618758F, 0.00867494995735709F, 0.00850341445300474F, 0.00833540843664957F, 0.00817085552784730F, 0.00800968110708622F, 0.00785181227191778F, 0.00769717779428456F, 0.00754570807900947F, 0.00739733512341117F, 0.00725199247801176F, 0.00710961520830429F, 0.00697013985754840F};

// Domain 3.5 ~ 11.436
static float ExpintTable4[63] = {0.00697013985754843F, 0.00595165118439979F, 0.00508661641561241F, 0.00435102957490895F, 0.00372481546087525F, 0.00319115004588169F, 0.00273590601139406F, 0.00234719870089483F, 0.00201501303487467F, 0.00173089598574009F, 0.00148770235377602F, 0.00127938403852772F, 0.00110081492605982F, 0.000947645033184157F, 0.000816178756486768F, 0.000703273036244310F, 0.000606252016086186F, 0.000522835399236460F, 0.000451078202821178F, 0.000389320017508240F, 0.000336142209771689F, 0.000290331773353231F, 0.000250850756880151F, 0.000216810375484428F, 0.000187449063132408F, 0.000162113845196945F, 0.000140244512382263F, 0.000121360161310043F, 0.000105047737015578F, 9.09522708167131e-05F, 7.87685555639048e-05F, 6.82340408359011e-05F, 5.91227645848651e-05F, 5.12401661828662e-05F, 4.44186497036028e-05F, 3.85137863511616e-05F, 3.34010618509128e-05F, 2.89730888669951e-05F, 2.51372165380621e-05F, 2.18134793867002e-05F, 1.89328364567230e-05F, 1.64356588152578e-05F, 1.42704297310207e-05F, 1.23926270802452e-05F, 1.07637619830281e-05F, 9.35055145753116e-06F, 8.12420610016641e-06F, 7.05981654290921e-06F, 6.13582477694144e-06F, 5.33356842622777e-06F, 4.63688775713486e-06F, 4.03178666455650e-06F, 3.50614011821845e-06F, 3.04944161624825e-06F, 2.65258510327885e-06F, 2.30767658985817e-06F, 2.00787137790676e-06F, 1.74723336968152e-06F, 1.52061342901041e-06F, 1.32354418525242e-06F, 1.15214903255314e-06F, 1.00306338807548e-06F, 8.73366540296160e-07F};


#endif //MMSE_CONST_H
