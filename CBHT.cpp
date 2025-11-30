#include <bits/stdc++.h>
using namespace std;

class CBHTNode {
public:
    string key;
    string value;
    CBHTNode* next;

    CBHTNode(const string& k, const string& v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class ClosedBucketHashTable {
private:
    vector<CBHTNode*> table;
    int size;

    int hashByLength(const string& word) {
        return word.length() % size;
    }

    int hashBySum(const string& word) {
        int charSum = 0;
        for (char c : word) {
            charSum += tolower(c);
        }
        return charSum % size;
    }

    int hashByFirstLetter(const string& word) {
        if (word.empty()) return 0;
        return (tolower(word[0]) - 'a') % size;
    }

    int hashByFirstTwoLetters(const string& word) {
        if (word.empty()) return 0;

        if (word.length() == 1) {
            return hashByFirstLetter(word);
        }

        string firstTwo = word.substr(0, 2);
        transform(firstTwo.begin(), firstTwo.end(), firstTwo.begin(), ::tolower);

        int hashVal = (firstTwo[0] - 'a') * 26 + (firstTwo[1] - 'a');
        return hashVal % size;
    }

    int getHashIndex(const string& word, const string& hashFunction) {
        if (hashFunction == "length") {
            return hashByLength(word);
        } else if (hashFunction == "sum") {
            return hashBySum(word);
        } else if (hashFunction == "first") {
            return hashByFirstLetter(word);
        } else if (hashFunction == "first_two") {
            return hashByFirstTwoLetters(word);
        } else {
            throw invalid_argument("Non valid funtion ");
        }
    }

public:
    ClosedBucketHashTable(int s = 100) {
        size = s;
        table.resize(size, nullptr);
    }

    ~ClosedBucketHashTable() {
        clear();
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            CBHTNode* current = table[i];
            while (current != nullptr) {
                CBHTNode* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }

    void insert(const string& word, const string& hashFunction = "length") {
        int index = getHashIndex(word, hashFunction);
        CBHTNode* newNode = new CBHTNode(word, word);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            CBHTNode* current = table[index];
            CBHTNode* prev = nullptr;

            while (current != nullptr) {
                if (current->key == word) {
                    current->value = word;
                    delete newNode;
                    return;
                }
                prev = current;
                current = current->next;
            }

            if (prev != nullptr) {
                prev->next = newNode;
            }
        }
    }

    bool remove(const string& word, const string& hashFunction = "length") {
        int index = getHashIndex(word, hashFunction);
        CBHTNode* current = table[index];
        CBHTNode* prev = nullptr;

        while (current != nullptr) {
            if (current->key == word) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }

        return false;
    }

    struct Statistics {
        int totalBucketsUsed;
        int totalCollisions;
        int maxChainLength;
        double avgChainLength;
    };

    Statistics getStatistics(const string& hashFunction = "length") {
        Statistics stats;
        stats.totalBucketsUsed = 0;
        stats.totalCollisions = 0;
        stats.maxChainLength = 0;
        stats.avgChainLength = 0.0;

        vector<int> bucketSizes;

        for (int i = 0; i < size; i++) {
            int chainLength = 0;
            CBHTNode* current = table[i];

            while (current != nullptr) {
                chainLength++;
                current = current->next;
            }

            if (chainLength > 0) {
                bucketSizes.push_back(chainLength);
                if (chainLength > 1) {
                    stats.totalCollisions += chainLength - 1;
                }
                if (chainLength > stats.maxChainLength) {
                    stats.maxChainLength = chainLength;
                }
            }
        }

        stats.totalBucketsUsed = bucketSizes.size();

        if (!bucketSizes.empty()) {
            double sum = 0;
            for (int length : bucketSizes) {
                sum += length;
            }
            stats.avgChainLength = sum / bucketSizes.size();
        }

        return stats;
    }

    void printBucketDistribution() {
        cout << "Distribution of buckets:" << endl;
        for (int i = 0; i < size; i++) {
            int count = 0;
            CBHTNode* current = table[i];
            while (current != nullptr) {
                count++;
                current = current->next;
            }
            if (count > 0) {
                cout << "Bucket " << i << ": " << count << " elements" << endl;
            }
        }
    }

    void printTable() {
        cout << "Content in the hesh table:" << endl;
        for (int i = 0; i < size; i++) {
            CBHTNode* current = table[i];
            if (current != nullptr) {
                cout << "Index " << i << ": ";
                while (current != nullptr) {
                    cout << current->key;
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
                cout << endl;
            }
        }
    }
};

vector<string> loadCommonWords() {
    return {
        "a", "ability", "able", "about", "above", "accept", "according", "account",
        "across", "act", "action", "activity", "actually", "add", "address",
        "administration", "admit", "adult", "affect", "after", "again", "against",
        "age", "agency", "agent", "ago", "agree", "agreement", "ahead", "air",
        "all", "allow", "almost", "alone", "along", "already", "also", "although",
        "always", "American", "among", "amount", "analysis", "and", "animal",
        "another", "answer", "any", "anyone", "anything", "appear", "apply",
        "approach", "area", "argue", "arm", "around", "arrive", "art", "article",
        "artist", "as", "ask", "assume", "at", "attack", "attention", "attorney",
        "audience", "author", "authority", "available", "avoid", "away", "baby",
        "back", "bad", "bag", "ball", "bank", "bar", "base", "be", "beat",
        "beautiful", "because", "become", "bed", "before", "begin", "behavior",
        "behind", "believe", "benefit", "best", "better", "between", "beyond",
        "big", "bill", "billion", "bit", "black", "blood", "blue", "board",
        "body", "book", "born", "both", "box", "boy", "break", "bring", "brother",
        "budget", "build", "building", "business", "but", "buy", "by", "call",
        "camera", "campaign", "can", "cancer", "candidate", "capital", "car",
        "card", "care", "career", "carry", "case", "catch", "cause", "cell",
        "center", "central", "century", "certain", "certainly", "chair",
        "challenge", "chance", "change", "character", "charge", "check", "child",
        "choice", "choose", "church", "citizen", "city", "civil", "claim",
        "class", "clear", "clearly", "close", "coach", "cold", "collection",
        "college", "color", "come", "commercial", "common", "community",
        "company", "compare", "computer", "concern", "condition", "conference",
        "Congress", "consider", "consumer", "contain", "continue", "control",
        "cost", "could", "country", "couple", "course", "court", "cover",
        "create", "crime", "cultural", "culture", "cup", "current", "customer",
        "cut", "dark", "data", "daughter", "day", "dead", "deal", "death",
        "debate", "decade", "decide", "decision", "deep", "defense", "degree",
        "Democrat", "democratic", "describe", "design", "despite", "detail",
        "determine", "develop", "development", "die", "difference", "different",
        "difficult", "dinner", "direction", "director", "discover", "discuss",
        "discussion", "disease", "do", "doctor", "dog", "door", "down", "draw",
        "dream", "drive", "drop", "drug", "during", "each", "early", "east",
        "easy", "eat", "economic", "economy", "edge", "education", "effect",
        "effort", "eight", "either", "election", "else", "employee", "end",
        "energy", "enjoy", "enough", "enter", "entire", "environment",
        "environmental", "especially", "establish", "even", "evening", "event",
        "ever", "every", "everybody", "everyone", "everything", "evidence",
        "exactly", "example", "executive", "exist", "expect", "experience",
        "expert", "explain", "eye", "face", "fact", "factor", "fail", "fall",
        "family", "far", "fast", "father", "fear", "federal", "feel", "feeling",
        "few", "field", "fight", "figure", "fill", "film", "final", "finally",
        "financial", "find", "fine", "finger", "finish", "fire", "firm", "first",
        "fish", "five", "floor", "fly", "focus", "follow", "food", "foot", "for",
        "force", "foreign", "forget", "form", "former", "forward", "four", "free",
        "friend", "from", "front", "full", "fund", "future", "game", "garden",
        "gas", "general", "generation", "get", "girl", "give", "glass", "go",
        "goal", "good", "government", "great", "green", "ground", "group", "grow",
        "growth", "guess", "gun", "guy", "hair", "half", "hand", "hang", "happen",
        "happy", "hard", "have", "he", "head", "health", "hear", "heart", "heat",
        "heavy", "help", "her", "here", "herself", "high", "him", "himself",
        "his", "history", "hit", "hold", "home", "hope", "hospital", "hot",
        "hotel", "hour", "house", "how", "however", "huge", "human", "hundred",
        "husband", "I", "idea", "identify", "if", "image", "imagine", "impact",
        "important", "improve", "in", "include", "including", "increase",
        "indeed", "indicate", "individual", "industry", "information", "inside",
        "instead", "institution", "interest", "interesting", "international",
        "interview", "into", "investment", "involve", "issue", "it", "item",
        "its", "itself", "job", "join", "just", "keep", "key", "kid", "kill",
        "kind", "kitchen", "know", "knowledge", "land", "language", "large",
        "last", "late", "later", "laugh", "law", "lawyer", "lay", "lead",
        "leader", "learn", "least", "leave", "left", "leg", "legal", "less",
        "let", "letter", "level", "lie", "life", "light", "like", "likely",
        "line", "list", "listen", "little", "live", "local", "long", "look",
        "lose", "loss", "lot", "love", "low", "machine", "magazine", "main",
        "maintain", "major", "majority", "make", "man", "manage", "management",
        "manager", "many", "market", "marriage", "material", "matter", "may",
        "maybe", "me", "mean", "measure", "media", "medical", "meet", "meeting",
        "member", "memory", "mention", "message", "method", "middle", "might",
        "military", "million", "mind", "minute", "miss", "mission", "model",
        "modern", "moment", "money", "month", "more", "morning", "most",
        "mother", "mouth", "move", "movement", "movie", "Mr", "Mrs", "much",
        "music", "must", "my", "myself", "name", "nation", "national", "natural",
        "nature", "near", "nearly", "necessary", "need", "network", "never",
        "new", "news", "newspaper", "next", "nice", "night", "no", "none",
        "nor", "north", "not", "note", "nothing", "notice", "now", "n't",
        "number", "occur", "of", "off", "offer", "office", "officer", "official",
        "often", "oh", "oil", "ok", "old", "on", "once", "one", "only", "onto",
        "open", "operation", "opportunity", "option", "or", "order",
        "organization", "other", "others", "our", "out", "outside", "over",
        "own", "owner", "page", "pain", "painting", "paper", "parent", "part",
        "participant", "particular", "particularly", "partner", "party", "pass",
        "past", "patient", "pattern", "pay", "peace", "people", "per", "perform",
        "performance", "perhaps", "period", "person", "personal", "phone",
        "physical", "pick", "picture", "piece", "place", "plan", "plant", "play",
        "player", "PM", "point", "police", "policy", "political", "politics",
        "poor", "popular", "population", "position", "positive", "possible",
        "power", "practice", "prepare", "present", "president", "pressure",
        "pretty", "prevent", "price", "private", "probably", "problem",
        "process", "produce", "product", "production", "professional",
        "professor", "program", "project", "property", "protect", "prove",
        "provide", "public", "pull", "purpose", "push", "put", "quality",
        "question", "quickly", "quite", "race", "radio", "raise", "range",
        "rate", "rather", "reach", "read", "ready", "real", "reality", "realize",
        "really", "reason", "receive", "recent", "recently", "recognize",
        "record", "red", "reduce", "reflect", "region", "relate", "relationship",
        "religious", "remain", "remember", "remove", "report", "represent",
        "Republican", "require", "research", "resource", "respond", "response",
        "responsibility", "rest", "result", "return", "reveal", "rich", "right",
        "rise", "risk", "road", "rock", "role", "room", "rule", "run", "safe",
        "same", "save", "say", "scene", "school", "science", "scientist", "score",
        "sea", "season", "seat", "second", "section", "security", "see", "seek",
        "seem", "sell", "send", "senior", "sense", "series", "serious", "serve",
        "service", "set", "seven", "several", "sex", "sexual", "shake", "share",
        "she", "shoot", "short", "shot", "should", "shoulder", "show", "side",
        "sign", "significant", "similar", "simple", "simply", "since", "sing",
        "single", "sister", "sit", "site", "situation", "six", "size", "skill",
        "skin", "small", "smile", "so", "social", "society", "soldier", "some",
        "somebody", "someone", "something", "sometimes", "son", "song", "soon",
        "sort", "sound", "source", "south", "southern", "space", "speak",
        "special", "specific", "speech", "spend", "sport", "spring", "staff",
        "stage", "stand", "standard", "star", "start", "state", "statement",
        "station", "stay", "step", "still", "stock", "stop", "store", "story",
        "strategy", "street", "strong", "structure", "student", "study", "stuff",
        "style", "subject", "success", "successful", "such", "suddenly", "suffer",
        "suggest", "summer", "support", "sure", "surface", "system", "table",
        "take", "talk", "task", "tax", "teach", "teacher", "team", "technology",
        "television", "tell", "ten", "tend", "term", "test", "than", "thank",
        "that", "the", "their", "them", "themselves", "then", "theory", "there",
        "these", "they", "thing", "think", "third", "this", "those", "though",
        "thought", "thousand", "threat", "three", "through", "throughout",
        "throw", "thus", "time", "to", "today", "together", "tonight", "too",
        "top", "total", "tough", "toward", "town", "trade", "traditional",
        "training", "travel", "treat", "treatment", "tree", "trial", "trip",
        "trouble", "true", "truth", "try", "turn", "TV", "two", "type", "under",
        "understand", "unit", "until", "up", "upon", "us", "use", "usually",
        "value", "various", "very", "victim", "view", "violence", "visit",
        "voice", "vote", "wait", "walk", "wall", "want", "war", "watch", "water",
        "way", "we", "weapon", "wear", "week", "weight", "well", "west",
        "western", "what", "whatever", "when", "where", "whether", "which",
        "while", "white", "who", "whole", "whom", "whose", "why", "wide", "wife",
        "will", "win", "wind", "window", "wish", "with", "within", "without",
        "woman", "wonder", "word", "work", "worker", "world", "worry", "would",
        "write", "writer", "wrong", "yard", "yeah", "year", "yes", "yet", "you",
        "young", "your", "yourself"
    };
}


void testHashTable() {
    cout << "\n=== Testing CBHT Hash Table ===" << endl;
    vector<string> words = loadCommonWords();
    cout << "Amount of words: " << words.size() << endl;
    vector<string> hashFunctions = {"length", "sum", "first", "first_two"};

    for (const auto& hashFunc : hashFunctions) {
        cout << "\n=== Testing with hash function: " << hashFunc << " ===" << endl;
        ClosedBucketHashTable cbht(50);

        for (const auto& word : words) {
            cbht.insert(word, hashFunc);
        }

        auto stats = cbht.getStatistics(hashFunc);
        cout << "Used buckets: " << stats.totalBucketsUsed << endl;
        cout << "Total collisions: " << stats.totalCollisions << endl;
        cout << "Max chain length: " << stats.maxChainLength << endl;
        cout << "Average chain length: " << stats.avgChainLength << endl;
    }
}

int main() {
    testHashTable();
    return 0;
}
}