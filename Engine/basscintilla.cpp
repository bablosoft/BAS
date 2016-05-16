#include "basscintilla.h"
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscistyle.h>
#include <Qsci/qsciapis.h>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    void BASScintilla::Init()
    {
        setUtf8(true);
        QsciLexerJavaScript * lex = new QsciLexerJavaScript(this);
        setLexer(lex);

        setCaretLineVisible(true);
        setCaretLineBackgroundColor(QColor("gainsboro"));

        setAutoIndent(true);
        setIndentationGuides(false);
        setIndentationsUseTabs(true);
        setIndentationWidth(4);

        setMarginsBackgroundColor(QColor("gainsboro"));
        setMarginLineNumbers(1, true);
        setMarginWidth(1, 50);

        setAutoCompletionSource(QsciScintilla::AcsAll);

        setAutoCompletionCaseSensitivity(true);
        setAutoCompletionReplaceWord(true);
        setAutoCompletionUseSingle(QsciScintilla::AcusExplicit);
        setAutoCompletionThreshold(1);


        setBraceMatching(QsciScintilla::SloppyBraceMatch);
        setMatchedBraceBackgroundColor(Qt::yellow);
        setUnmatchedBraceForegroundColor(Qt::blue);

        setFolding(QsciScintilla::PlainFoldStyle);

        QsciAPIs *api = new QsciAPIs(lex);
        api->load(":/engine/text/apilist.txt");

        api->prepare();
        Searched = false;


    }
    void BASScintilla::keyPressEvent(QKeyEvent *e)
    {
        if((e->modifiers() == Qt::CTRL) && (e->key() == Qt::Key_Space))
        {
            autoCompleteFromAll();
            return;
        }
        if((e->modifiers() == Qt::CTRL) && (e->key() == Qt::Key_F))
        {
            emit ShowFinder();
            return;
        }
        if(e->key() == Qt::Key_F3)
        {
            FindNext(true);
            return;
        }
        QsciScintilla::keyPressEvent(e);
    }

    void BASScintilla::FindNext(bool Direction)
    {
        if(Term.isEmpty())
        {
            emit ShowFinder();
        }else
        {
            if(!Searched || LastDirection != Direction)
            {
                findFirst(Term,false,false,false,true,Direction);
                Searched = true;
                LastDirection = Direction;
            }
            findNext();
        }

    }


    void BASScintilla::SetSearchTerm(const QString &Term)
    {
        Searched = false;
        this->Term = Term;
        FindNext(true);
    }
}
