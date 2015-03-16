#define STRINGS_LENGTH 1536
#define NAME_LENGTH 128
typedef struct xmusic_songs
{	
	gchar name[NAME_LENGTH];
	gchar uri[STRINGS_LENGTH];
	struct xmusic_songs* next;
	struct xmusic_songs* pre;
} xmusic_songs;

typedef struct xmusic_lists
{
	gchar name[STRINGS_LENGTH];
	gint num;
	struct xmusic_songs* foucs;
	struct xmusic_songs* last;
	struct xmusic_songs* songs;
	struct xmusic_lists* next;
} xmusic_lists;


void xmusic_init(struct xmusic *xmusic);
void xmusic_play_pause();
void stop_pressed();
void xmusic_quit();
void play_pre();
void play_next();
void play_this_num(gint row);
void add_new_songs(gchar *song_path);
