// This file is generated by kconfig_compiler from parleypractice.kcfg.
// All changes you do to this file will be lost.

#include "practiceprefs.h"

#include <kglobal.h>
#include <QtCore/QFile>

class PracticePrefsHelper
{
  public:
    PracticePrefsHelper() : q(0) {}
    ~PracticePrefsHelper() { delete q; }
    PracticePrefs *q;
};
K_GLOBAL_STATIC(PracticePrefsHelper, s_globalPracticePrefs)
PracticePrefs *PracticePrefs::self()
{
  if (!s_globalPracticePrefs->q) {
    new PracticePrefs;
    s_globalPracticePrefs->q->readConfig();
  }

  return s_globalPracticePrefs->q;
}

PracticePrefs::PracticePrefs(  )
  : KConfigSkeleton( QLatin1String( "parleypracticerc" ) )
{
  Q_ASSERT(!s_globalPracticePrefs->q);
  s_globalPracticePrefs->q = this;
  setCurrentGroup( QLatin1String( "PracticeOptions" ) );

  KConfigSkeleton::ItemBool  *itemBlock;
  itemBlock = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Block" ), mBlock, false );
  addItem( itemBlock, QLatin1String( "Block" ) );
  KConfigSkeleton::ItemBool  *itemExpire;
  itemExpire = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Expire" ), mExpire, false );
  addItem( itemExpire, QLatin1String( "Expire" ) );
  KConfigSkeleton::ItemBool  *itemAltLearn;
  itemAltLearn = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "AltLearn" ), mAltLearn, false );
  addItem( itemAltLearn, QLatin1String( "AltLearn" ) );
  KConfigSkeleton::ItemBool  *itemTestOrderLesson;
  itemTestOrderLesson = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "TestOrderLesson" ), mTestOrderLesson, true );
  addItem( itemTestOrderLesson, QLatin1String( "TestOrderLesson" ) );
  KConfigSkeleton::ItemInt  *itemTestNumberOfEntries;
  itemTestNumberOfEntries = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "TestNumberOfEntries" ), mTestNumberOfEntries, 20 );
  addItem( itemTestNumberOfEntries, QLatin1String( "TestNumberOfEntries" ) );
  KConfigSkeleton::ItemBool  *itemSwapDirection;
  itemSwapDirection = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "SwapDirection" ), mSwapDirection, false );
  addItem( itemSwapDirection, QLatin1String( "SwapDirection" ) );
  KConfigSkeleton::ItemBool  *itemPracticeTimeout;
  itemPracticeTimeout = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "PracticeTimeout" ), mPracticeTimeout, false );
  addItem( itemPracticeTimeout, QLatin1String( "PracticeTimeout" ) );
  QList<KConfigSkeleton::ItemEnum::Choice> valuesPracticeTimeoutMode;
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "Show" );
    valuesPracticeTimeoutMode.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "Continue" );
    valuesPracticeTimeoutMode.append( choice );
  }
  KConfigSkeleton::ItemEnum  *itemPracticeTimeoutMode;
  itemPracticeTimeoutMode = new KConfigSkeleton::ItemEnum( currentGroup(), QLatin1String( "PracticeTimeoutMode" ), mPracticeTimeoutMode, valuesPracticeTimeoutMode, EnumPracticeTimeoutMode::Show );
  addItem( itemPracticeTimeoutMode, QLatin1String( "PracticeTimeoutMode" ) );
  KConfigSkeleton::ItemInt  *itemPracticeTimeoutTimePerAnswer;
  itemPracticeTimeoutTimePerAnswer = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeTimeoutTimePerAnswer" ), mPracticeTimeoutTimePerAnswer, 20 );
  addItem( itemPracticeTimeoutTimePerAnswer, QLatin1String( "PracticeTimeoutTimePerAnswer" ) );
  KConfigSkeleton::ItemBool  *itemSuggestions;
  itemSuggestions = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Suggestions" ), mSuggestions, false );
  addItem( itemSuggestions, QLatin1String( "Suggestions" ) );
  KConfigSkeleton::ItemBool  *itemIgnoreAccentMistakes;
  itemIgnoreAccentMistakes = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "IgnoreAccentMistakes" ), mIgnoreAccentMistakes, false );
  addItem( itemIgnoreAccentMistakes, QLatin1String( "IgnoreAccentMistakes" ) );
  KConfigSkeleton::ItemBool  *itemIgnoreCapitalizationMistakes;
  itemIgnoreCapitalizationMistakes = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "IgnoreCapitalizationMistakes" ), mIgnoreCapitalizationMistakes, false );
  addItem( itemIgnoreCapitalizationMistakes, QLatin1String( "IgnoreCapitalizationMistakes" ) );
  KConfigSkeleton::ItemBool  *itemSplitTranslations;
  itemSplitTranslations = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "SplitTranslations" ), mSplitTranslations, false );
  addItem( itemSplitTranslations, QLatin1String( "SplitTranslations" ) );
  KConfigSkeleton::ItemBool  *itemPeriods;
  itemPeriods = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Periods" ), mPeriods, true );
  addItem( itemPeriods, QLatin1String( "Periods" ) );
  KConfigSkeleton::ItemBool  *itemColons;
  itemColons = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Colons" ), mColons, false );
  addItem( itemColons, QLatin1String( "Colons" ) );
  KConfigSkeleton::ItemBool  *itemSemicolons;
  itemSemicolons = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Semicolons" ), mSemicolons, true );
  addItem( itemSemicolons, QLatin1String( "Semicolons" ) );
  KConfigSkeleton::ItemBool  *itemCommas;
  itemCommas = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "Commas" ), mCommas, false );
  addItem( itemCommas, QLatin1String( "Commas" ) );
  KConfigSkeleton::ItemBool  *itemShowMore;
  itemShowMore = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "ShowMore" ), mShowMore, true );
  addItem( itemShowMore, QLatin1String( "ShowMore" ) );
  KConfigSkeleton::ItemBool  *itemSkipKnownEnabled;
  itemSkipKnownEnabled = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "SkipKnownEnabled" ), mSkipKnownEnabled, true );
  addItem( itemSkipKnownEnabled, QLatin1String( "SkipKnownEnabled" ) );
  KConfigSkeleton::ItemBool  *itemCountSynonymsAsCorrect;
  itemCountSynonymsAsCorrect = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "CountSynonymsAsCorrect" ), mCountSynonymsAsCorrect, true );
  addItem( itemCountSynonymsAsCorrect, QLatin1String( "CountSynonymsAsCorrect" ) );
  KConfigSkeleton::ItemBool  *itemPracticeImagesEnabled;
  itemPracticeImagesEnabled = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "PracticeImagesEnabled" ), mPracticeImagesEnabled, true );
  addItem( itemPracticeImagesEnabled, QLatin1String( "PracticeImagesEnabled" ) );
  KConfigSkeleton::ItemBool  *itemPracticeSoundEnabled;
  itemPracticeSoundEnabled = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "PracticeSoundEnabled" ), mPracticeSoundEnabled, true );
  addItem( itemPracticeSoundEnabled, QLatin1String( "PracticeSoundEnabled" ) );

  setCurrentGroup( QLatin1String( "Appearance" ) );

  KConfigSkeleton::ItemBool  *itemShowSearch;
  itemShowSearch = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "ShowSearch" ), mShowSearch, true );
  addItem( itemShowSearch, QLatin1String( "ShowSearch" ) );
  KConfigSkeleton::ItemBool  *itemShowSublessonentries;
  itemShowSublessonentries = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "ShowSublessonentries" ), mShowSublessonentries, false );
  addItem( itemShowSublessonentries, QLatin1String( "ShowSublessonentries" ) );
  KConfigSkeleton::ItemBool  *itemTableLessonColumnVisible;
  itemTableLessonColumnVisible = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "TableLessonColumnVisible" ), mTableLessonColumnVisible, false );
  addItem( itemTableLessonColumnVisible, QLatin1String( "TableLessonColumnVisible" ) );
  KConfigSkeleton::ItemBool  *itemTableActiveColumnVisible;
  itemTableActiveColumnVisible = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "TableActiveColumnVisible" ), mTableActiveColumnVisible, false );
  addItem( itemTableActiveColumnVisible, QLatin1String( "TableActiveColumnVisible" ) );
  QList<KConfigSkeleton::ItemEnum::Choice> valuesLessonEditingSelection;
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "CurrentLesson" );
    valuesLessonEditingSelection.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "LessonsInQuery" );
    valuesLessonEditingSelection.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "AllLessons" );
    valuesLessonEditingSelection.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "UserFiltered" );
    valuesLessonEditingSelection.append( choice );
  }
  KConfigSkeleton::ItemEnum  *itemLessonEditingSelection;
  itemLessonEditingSelection = new KConfigSkeleton::ItemEnum( currentGroup(), QLatin1String( "LessonEditingSelection" ), mLessonEditingSelection, valuesLessonEditingSelection, EnumLessonEditingSelection::CurrentLesson );
  addItem( itemLessonEditingSelection, QLatin1String( "LessonEditingSelection" ) );
  QList<int> defaultMainWindowSplitter;
  defaultMainWindowSplitter.append( 150 );
  defaultMainWindowSplitter.append(  400 );

  KConfigSkeleton::ItemIntList  *itemMainWindowSplitter;
  itemMainWindowSplitter = new KConfigSkeleton::ItemIntList( currentGroup(), QLatin1String( "MainWindowSplitter" ), mMainWindowSplitter, defaultMainWindowSplitter );
  addItem( itemMainWindowSplitter, QLatin1String( "MainWindowSplitter" ) );
  KConfigSkeleton::ItemFont  *itemTableFont;
  itemTableFont = new KConfigSkeleton::ItemFont( currentGroup(), QLatin1String( "TableFont" ), mTableFont, KGlobalSettings::generalFont() );
  addItem( itemTableFont, QLatin1String( "TableFont" ) );
  KConfigSkeleton::ItemFont  *itemIPAFont;
  itemIPAFont = new KConfigSkeleton::ItemFont( currentGroup(), QLatin1String( "IPAFont" ), mIPAFont, KGlobalSettings::generalFont() );
  addItem( itemIPAFont, QLatin1String( "IPAFont" ) );
  KConfigSkeleton::ItemInt  *itemCurrentCol;
  itemCurrentCol = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "CurrentCol" ), mCurrentCol, 2 );
  addItem( itemCurrentCol, QLatin1String( "CurrentCol" ) );
  KConfigSkeleton::ItemInt  *itemCurrentRow;
  itemCurrentRow = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "CurrentRow" ), mCurrentRow, 0 );
  addItem( itemCurrentRow, QLatin1String( "CurrentRow" ) );
  KConfigSkeleton::ItemBool  *itemUseGradeColors;
  itemUseGradeColors = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "UseGradeColors" ), mUseGradeColors, true );
  addItem( itemUseGradeColors, QLatin1String( "UseGradeColors" ) );
  KConfigSkeleton::ItemColor  *itemGradeColor[8];
  itemGradeColor[0] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor0" ), mGradeColor[0], QColor( 0, 0, 0 ) );
  addItem( itemGradeColor[0], QLatin1String( "GradeColor0" ) );
  itemGradeColor[1] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor1" ), mGradeColor[1], QColor( 140, 25, 25 ) );
  addItem( itemGradeColor[1], QLatin1String( "GradeColor1" ) );
  itemGradeColor[2] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor2" ), mGradeColor[2], QColor( 140, 25, 25 ) );
  addItem( itemGradeColor[2], QLatin1String( "GradeColor2" ) );
  itemGradeColor[3] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor3" ), mGradeColor[3], QColor( 140, 25, 25 ) );
  addItem( itemGradeColor[3], QLatin1String( "GradeColor3" ) );
  itemGradeColor[4] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor4" ), mGradeColor[4], QColor( 25, 140, 25 ) );
  addItem( itemGradeColor[4], QLatin1String( "GradeColor4" ) );
  itemGradeColor[5] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor5" ), mGradeColor[5], QColor( 25, 140, 25 ) );
  addItem( itemGradeColor[5], QLatin1String( "GradeColor5" ) );
  itemGradeColor[6] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor6" ), mGradeColor[6], QColor( 25, 140, 25 ) );
  addItem( itemGradeColor[6], QLatin1String( "GradeColor6" ) );
  itemGradeColor[7] = new KConfigSkeleton::ItemColor( currentGroup(), QLatin1String( "GradeColor7" ), mGradeColor[7], QColor( 25, 140, 25 ) );
  addItem( itemGradeColor[7], QLatin1String( "GradeColor7" ) );

  setCurrentGroup( QLatin1String( "Thresholds" ) );

  KConfigSkeleton::ItemInt  *itemPracticeMinimumTimesAsked;
  itemPracticeMinimumTimesAsked = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeMinimumTimesAsked" ), mPracticeMinimumTimesAsked, 0 );
  addItem( itemPracticeMinimumTimesAsked, QLatin1String( "PracticeMinimumTimesAsked" ) );
  KConfigSkeleton::ItemInt  *itemPracticeMaximumTimesAsked;
  itemPracticeMaximumTimesAsked = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeMaximumTimesAsked" ), mPracticeMaximumTimesAsked, 1000 );
  addItem( itemPracticeMaximumTimesAsked, QLatin1String( "PracticeMaximumTimesAsked" ) );
  KConfigSkeleton::ItemInt  *itemPracticeMinimumWrongCount;
  itemPracticeMinimumWrongCount = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeMinimumWrongCount" ), mPracticeMinimumWrongCount, 0 );
  addItem( itemPracticeMinimumWrongCount, QLatin1String( "PracticeMinimumWrongCount" ) );
  KConfigSkeleton::ItemInt  *itemPracticeMaximumWrongCount;
  itemPracticeMaximumWrongCount = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeMaximumWrongCount" ), mPracticeMaximumWrongCount, 1000 );
  addItem( itemPracticeMaximumWrongCount, QLatin1String( "PracticeMaximumWrongCount" ) );
  KConfigSkeleton::ItemInt  *itemPracticeMinimumGrade;
  itemPracticeMinimumGrade = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeMinimumGrade" ), mPracticeMinimumGrade, 0 );
  addItem( itemPracticeMinimumGrade, QLatin1String( "PracticeMinimumGrade" ) );
  KConfigSkeleton::ItemInt  *itemPracticeMaximumGrade;
  itemPracticeMaximumGrade = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "PracticeMaximumGrade" ), mPracticeMaximumGrade, 7 );
  addItem( itemPracticeMaximumGrade, QLatin1String( "PracticeMaximumGrade" ) );
  KConfigSkeleton::ItemBool  *itemWordTypesInPracticeEnabled;
  itemWordTypesInPracticeEnabled = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "WordTypesInPracticeEnabled" ), mWordTypesInPracticeEnabled, false );
  addItem( itemWordTypesInPracticeEnabled, QLatin1String( "WordTypesInPracticeEnabled" ) );
  KConfigSkeleton::ItemStringList  *itemWordTypesInPractice;
  itemWordTypesInPractice = new KConfigSkeleton::ItemStringList( currentGroup(), QLatin1String( "WordTypesInPractice" ), mWordTypesInPractice );
  addItem( itemWordTypesInPractice, QLatin1String( "WordTypesInPractice" ) );
  KConfigSkeleton::ItemStringList  *itemSubWordTypesInPractice;
  itemSubWordTypesInPractice = new KConfigSkeleton::ItemStringList( currentGroup(), QLatin1String( "SubWordTypesInPractice" ), mSubWordTypesInPractice );
  addItem( itemSubWordTypesInPractice, QLatin1String( "SubWordTypesInPractice" ) );

  setCurrentGroup( QLatin1String( "PracticeManager" ) );

  KConfigSkeleton::ItemInt  *itemQuestionLanguage;
  itemQuestionLanguage = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "QuestionLanguage" ), mQuestionLanguage, 0 );
  addItem( itemQuestionLanguage, QLatin1String( "QuestionLanguage" ) );
  KConfigSkeleton::ItemInt  *itemSolutionLanguage;
  itemSolutionLanguage = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "SolutionLanguage" ), mSolutionLanguage, 1 );
  addItem( itemSolutionLanguage, QLatin1String( "SolutionLanguage" ) );
  KConfigSkeleton::ItemBool  *itemShowSolutionAfterAnswer;
  itemShowSolutionAfterAnswer = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "ShowSolutionAfterAnswer" ), mShowSolutionAfterAnswer, true );
  addItem( itemShowSolutionAfterAnswer, QLatin1String( "ShowSolutionAfterAnswer" ) );
  KConfigSkeleton::ItemInt  *itemShowSolutionAfterAnswerTime;
  itemShowSolutionAfterAnswerTime = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ShowSolutionAfterAnswerTime" ), mShowSolutionAfterAnswerTime, 0 );
  addItem( itemShowSolutionAfterAnswerTime, QLatin1String( "ShowSolutionAfterAnswerTime" ) );
  QList<KConfigSkeleton::ItemEnum::Choice> valuesTestType;
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "MixedLettersTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "ArticleTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "MultipleChoiceTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "ComparisonTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "WrittenTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "ConjugationTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "ExampleTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "SynonymTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "ParaphraseTest" );
    valuesTestType.append( choice );
  }
  {
    KConfigSkeleton::ItemEnum::Choice choice;
    choice.name = QLatin1String( "AntonymTest" );
    valuesTestType.append( choice );
  }
  KConfigSkeleton::ItemEnum  *itemTestType;
  itemTestType = new KConfigSkeleton::ItemEnum( currentGroup(), QLatin1String( "TestType" ), mTestType, valuesTestType, EnumTestType::WrittenTest );
  addItem( itemTestType, QLatin1String( "TestType" ) );
  KConfigSkeleton::ItemBool  *itemComparisonIncludeAdjective;
  itemComparisonIncludeAdjective = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "ComparisonIncludeAdjective" ), mComparisonIncludeAdjective, true );
  addItem( itemComparisonIncludeAdjective, QLatin1String( "ComparisonIncludeAdjective" ) );
  KConfigSkeleton::ItemBool  *itemComparisonIncludeAdverb;
  itemComparisonIncludeAdverb = new KConfigSkeleton::ItemBool( currentGroup(), QLatin1String( "ComparisonIncludeAdverb" ), mComparisonIncludeAdverb, true );
  addItem( itemComparisonIncludeAdverb, QLatin1String( "ComparisonIncludeAdverb" ) );
  KConfigSkeleton::ItemInt  *itemBlockItem[8];
  itemBlockItem[0] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem0" ), mBlockItem[0], 0 );
  addItem( itemBlockItem[0], QLatin1String( "BlockItem0" ) );
  itemBlockItem[1] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem1" ), mBlockItem[1], 86400 );
  addItem( itemBlockItem[1], QLatin1String( "BlockItem1" ) );
  itemBlockItem[2] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem2" ), mBlockItem[2], 172800 );
  addItem( itemBlockItem[2], QLatin1String( "BlockItem2" ) );
  itemBlockItem[3] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem3" ), mBlockItem[3], 345600 );
  addItem( itemBlockItem[3], QLatin1String( "BlockItem3" ) );
  itemBlockItem[4] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem4" ), mBlockItem[4], 604800 );
  addItem( itemBlockItem[4], QLatin1String( "BlockItem4" ) );
  itemBlockItem[5] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem5" ), mBlockItem[5], 1209600 );
  addItem( itemBlockItem[5], QLatin1String( "BlockItem5" ) );
  itemBlockItem[6] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem6" ), mBlockItem[6], 2592000 );
  addItem( itemBlockItem[6], QLatin1String( "BlockItem6" ) );
  itemBlockItem[7] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "BlockItem7" ), mBlockItem[7], 5184000 );
  addItem( itemBlockItem[7], QLatin1String( "BlockItem7" ) );
  KConfigSkeleton::ItemInt  *itemExpireItem[8];
  itemExpireItem[0] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem0" ), mExpireItem[0], 0 );
  addItem( itemExpireItem[0], QLatin1String( "ExpireItem0" ) );
  itemExpireItem[1] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem1" ), mExpireItem[1], 172800 );
  addItem( itemExpireItem[1], QLatin1String( "ExpireItem1" ) );
  itemExpireItem[2] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem2" ), mExpireItem[2], 345600 );
  addItem( itemExpireItem[2], QLatin1String( "ExpireItem2" ) );
  itemExpireItem[3] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem3" ), mExpireItem[3], 604800 );
  addItem( itemExpireItem[3], QLatin1String( "ExpireItem3" ) );
  itemExpireItem[4] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem4" ), mExpireItem[4], 1209600 );
  addItem( itemExpireItem[4], QLatin1String( "ExpireItem4" ) );
  itemExpireItem[5] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem5" ), mExpireItem[5], 2592000 );
  addItem( itemExpireItem[5], QLatin1String( "ExpireItem5" ) );
  itemExpireItem[6] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem6" ), mExpireItem[6], 5184000 );
  addItem( itemExpireItem[6], QLatin1String( "ExpireItem6" ) );
  itemExpireItem[7] = new KConfigSkeleton::ItemInt( currentGroup(), QLatin1String( "ExpireItem7" ), mExpireItem[7], 10368000 );
  addItem( itemExpireItem[7], QLatin1String( "ExpireItem7" ) );
}

PracticePrefs::~PracticePrefs()
{
  if (!s_globalPracticePrefs.isDestroyed()) {
    s_globalPracticePrefs->q = 0;
  }
}

