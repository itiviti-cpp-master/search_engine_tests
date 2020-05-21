#include <gtest/gtest.h>
#include "searcher.h"

using namespace searcher;

TEST(SearchEngineBasicTests, AddSimpleDocument)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher s;
    s.add_document(simple_file);
    auto [begin, end] = s.search("engine");
    ASSERT_NE(begin, end);
    ASSERT_EQ(*begin, simple_file);
	begin++;
	ASSERT_EQ(begin, end);
}

TEST(SearchEngineBasicTests, AddEmptyDocument)
{
    Searcher::Filename empty_file("test/etc/empty_file.txt");
	Searcher s;
    s.add_document(empty_file);
    auto [begin, end] = s.search("engine");
    
    ASSERT_EQ(begin, end);
}

TEST(SearchEngineBasicTests, AddTwoDocuments)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(call_me_ishmael);

	{
		auto [begin, end] = s.search("engine");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Ishmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Boris");
        ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineBasicTests, PunctBeforeAndAfter)
{
	Searcher::Filename punct_before_and_after("test/etc/punct_before_and_after.txt");
	
	Searcher s;
	s.add_document(punct_before_and_after);

	{
		auto [begin, end] = s.search("Ishmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, punct_before_and_after);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Boris");
        ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineBasicTests, PunctInTheMiddle)
{
	Searcher::Filename punct_in_the_middle("test/etc/punct_in_the_middle.txt");
	
	Searcher s;
	s.add_document(punct_in_the_middle);

	{
		auto [begin, end] = s.search("Is-hma--el");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, punct_in_the_middle);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Ishmael");
        ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineBasicTests, TextWithoutSpaceSymbols)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	Searcher::Filename text_without_space_symbols("test/etc/text_without_space_symbols.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(call_me_ishmael);
	s.add_document(text_without_space_symbols);

	{
		auto [begin, end] = s.search("engine");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Ishmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("CallmeIshmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, text_without_space_symbols);
		begin++;
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineBasicTests, ThreePairsOfIterators)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(call_me_ishmael);

	auto [begin_first, end_first] = s.search("engine");
	auto [begin_second, end_second] = s.search("Ishmael");
	auto [begin_third, end_third] = s.search("Boris");

	ASSERT_EQ(*begin_first, simple_file);
	ASSERT_NE(begin_first, end_first);
	begin_first++;
	ASSERT_EQ(begin_first, end_first);

	ASSERT_EQ(*begin_second, call_me_ishmael);
	ASSERT_NE(begin_second, end_second);
	begin_second++;
	ASSERT_EQ(begin_second, end_second);

	ASSERT_EQ(begin_third, end_third);
}

TEST(SearchEngineBasicTests, WordInTheTwoDocuments)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(call_me_ishmael);

	auto [begin, end] = s.search("the");
	ASSERT_NE(begin, end);
	ASSERT_TRUE(*begin == simple_file || *begin == call_me_ishmael);
	begin++;
	ASSERT_NE(begin, end);
	ASSERT_TRUE(*begin == simple_file || *begin == call_me_ishmael);
	begin++;
	ASSERT_EQ(begin, end);
}

TEST(SearchEngineBasicTests, NoDocumentsInSearcher)
{
	Searcher s;

	auto [begin, end] = s.search("the");
	ASSERT_EQ(begin, end);
}

TEST(SearchEngineBasicTests, ExtraSpacesAndPunctInFile)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename extra_spaces_and_punct("test/etc/extra_spaces_and_punct.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(extra_spaces_and_punct);

	{
		auto [begin, end] = s.search("the");
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == extra_spaces_and_punct);
		begin++;
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == extra_spaces_and_punct);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("\"the speed\"");
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == extra_spaces_and_punct);
		begin++;
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == extra_spaces_and_punct);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("\"the speed of query\"");
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineBasicTests, AddSameDocumentTwice)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(call_me_ishmael);
	s.add_document(simple_file);

	{
		auto [begin, end] = s.search("engine");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Boris");
        ASSERT_EQ(begin, end);
	}
}



TEST(SearchQueryTests, TwoWordsInTheQuery)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(call_me_ishmael);

	{
		auto [begin, end] = s.search("the city");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}

	{
		auto [begin, end] = s.search("the implementation");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchQueryTests, TwoWordsWithQuotesInTheQuery)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename simple_file_copy("test/etc/simple_file_copy.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(simple_file_copy);
	s.add_document(call_me_ishmael);

	{
		auto [begin, end] = s.search("\"the city\"");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}

	{
		auto [begin, end] = s.search("\"the implementation\"");
		ASSERT_EQ(begin, end);
	}

	{
		auto [begin, end] = s.search("\"the query\"");
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == simple_file_copy);
		begin++;
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == simple_file_copy);
		begin++;
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchQueryTests, ComplexQuery)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename simple_file_copy("test/etc/simple_file_copy.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(simple_file_copy);
	s.add_document(call_me_ishmael);

	{
		auto [begin, end] = s.search("\"the city\" \"Call me Ishmael\" Manhattoes \"Corlears Hook\" wharves");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}

	{
		auto [begin, end] = s.search("the implementation of Ishmael");
		ASSERT_EQ(begin, end);
	}

	{
		auto [begin, end] = s.search("\"the query\" \"A goal\" the the the the the optimize");
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == simple_file_copy);
		begin++;
		ASSERT_NE(begin, end);
		ASSERT_TRUE(*begin == simple_file || *begin == simple_file_copy);
		begin++;
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchQueryTests, IncorrectQuery)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	
	Searcher s;
    s.add_document(simple_file);

	ASSERT_THROW(s.search(""), Searcher::BadQuery);
	ASSERT_THROW(s.search(" "), Searcher::BadQuery);
	ASSERT_THROW(s.search(" \"the query"), Searcher::BadQuery);
	ASSERT_THROW(s.search(" the query\""), Searcher::BadQuery);
	ASSERT_THROW(s.search("(_*_)"), Searcher::BadQuery);
}

TEST(SearchEngineRemoveDocumentTests, RemoveDocumentSimpleTest)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher s;

    s.add_document(simple_file);
	{
		auto [begin, end] = s.search("engine");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}

    s.remove_document(simple_file);
	{
		auto [begin, end] = s.search("engine");		
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineRemoveDocumentTests, RemoveSeveralDocuments)
{
    Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename simple_file_copy("test/etc/simple_file_copy.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");
	
	Searcher s;
    s.add_document(simple_file);
	s.add_document(simple_file_copy);
	s.add_document(call_me_ishmael);

	s.remove_document(simple_file_copy);
	{
		auto [begin, end] = s.search("engine");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}

    s.remove_document(simple_file);
	{
		auto [begin, end] = s.search("engine");		
		ASSERT_EQ(begin, end);
	}

	{
		auto [begin, end] = s.search("Ishmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}

	s.remove_document(call_me_ishmael);
	{
		auto [begin, end] = s.search("Ishmael");		
		ASSERT_EQ(begin, end);
	}
}

TEST(SearchEngineRemoveDocumentTests, IncorrectRemoveCall)
{
	Searcher::Filename simple_file("test/etc/simple_file.txt");
	Searcher::Filename call_me_ishmael("test/etc/call_me_ishmael.txt");

	Searcher s;
	s.remove_document(simple_file);
	s.search("engine");

    s.add_document(simple_file);
	s.remove_document(call_me_ishmael);
	{
		auto [begin, end] = s.search("engine");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, simple_file);
		begin++;
		ASSERT_EQ(begin, end);
	}
	
	s.add_document(call_me_ishmael);
	s.remove_document(simple_file);
	{
		auto [begin, end] = s.search("engine");		
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Ishmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}

	s.remove_document(simple_file);
	{
		auto [begin, end] = s.search("Ishmael");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, call_me_ishmael);
		begin++;
		ASSERT_EQ(begin, end);
	}
}


TEST(SearchEngineStressTests, StressTest)
{
	Searcher::Filename Frankenstein("test/etc/Frankenstein.txt");
	Searcher::Filename Pride_and_Prejudice("test/etc/Pride_and_Prejudice.txt");
	Searcher::Filename The_Strange_Case_Of_Dr_Jekyll_And_Mr_Hyde("test/etc/The_Strange_Case_Of_Dr_Jekyll_And_Mr_Hyde.txt");
	Searcher::Filename Moby_Dick("test/etc/Moby_Dick.txt");
	Searcher::Filename Alices_Adventures_in_Wonderland("test/etc/Alices_Adventures_in_Wonderland.txt");
	
	Searcher s;
	s.add_document(Frankenstein);
	s.add_document(Pride_and_Prejudice);
	s.add_document(The_Strange_Case_Of_Dr_Jekyll_And_Mr_Hyde);

	{
		auto [begin, end] = s.search("Prejudice");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, Pride_and_Prejudice);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("Frankenstein");
		ASSERT_NE(begin, end);
        ASSERT_EQ(*begin, Frankenstein);
		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("daughters");
		ASSERT_NE(begin, end);
        
		ASSERT_TRUE(
			*begin == Pride_and_Prejudice ||
			*begin == Moby_Dick
		);

		begin++;
		ASSERT_NE(begin, end);
		ASSERT_TRUE(
			*begin == Pride_and_Prejudice ||
			*begin == Moby_Dick
		);

		begin++;
		ASSERT_EQ(begin, end);
	}

	s.remove_document(Frankenstein);
	s.remove_document(Alices_Adventures_in_Wonderland);
	s.remove_document(Moby_Dick);
	{
		auto [begin, end] = s.search("daughters");
		ASSERT_NE(begin, end);
		ASSERT_EQ(*begin, Pride_and_Prejudice);

		begin++;
		ASSERT_EQ(begin, end);
	}
	{
		auto [begin, end] = s.search("ksfhiwefhliwehapoheioi");
        ASSERT_EQ(begin, end);
	}
}