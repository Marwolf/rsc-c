#include "utility.h"

int sin_cos_512[512] = {0};
int sin_cos_2048[2048] = {0};

int BITMASK[] = {0,          1,          3,         7,         15,
                 31,         63,         127,       255,       511,
                 1023,       2047,       4095,      8191,      16383,
                 32767,      65535,      0x1ffff,   0x3ffff,   0x7ffff,
                 0xfffff,    0x1fffff,   0x3fffff,  0x7fffff,  0xffffff,
                 0x1ffffff,  0x3ffffff,  0x7ffffff, 0xfffffff, 0x1fffffff,
                 0x3fffffff, 0x7fffffff, -1};

// TODO typed
int certificate_items[][2] = {
    {517, 151},  {521, 152}, {519, 153},  {518, 155},  {528, 170},  {529, 171},
    {532, 172},  {530, 173}, {1271, 220}, {536, 369},  {535, 370},  {534, 372},
    {533, 373},  {520, 383}, {531, 384},  {1272, 483}, {1273, 486}, {1275, 492},
    {1274, 495}, {631, 545}, {630, 546},  {629, 554},  {628, 555},  {713, 633},
    {712, 634},  {711, 635}, {1270, 814}};

void init_utility_global() {
    for (int i = 0; i < 256; i++) {
        sin_cos_512[i] = (int)(sin((double)i * 0.02454369) * 32768);
        sin_cos_512[i + 256] = (int)(cos((double)i * 0.02454369) * 32768);
    }

    /* sin(i) = sin((i / 256.0f) * (M_PI / 2)) */
    for (int i = 0; i < 1024; i++) {
        sin_cos_2048[i] = (int)(sin((double)i * 0.00613592315) * 32768);
        sin_cos_2048[i + 1024] = (int)(cos((double)i * 0.00613592315) * 32768);
    }
}

#ifdef RENDER_3DS_GL
int _3ds_gl_framebuffer_offsets_x[] = {
    0,     2,     8,     10,    32,    34,    40,    42,    1920,  1922,  1928,
    1930,  1952,  1954,  1960,  1962,  3840,  3842,  3848,  3850,  3872,  3874,
    3880,  3882,  5760,  5762,  5768,  5770,  5792,  5794,  5800,  5802,  7680,
    7682,  7688,  7690,  7712,  7714,  7720,  7722,  9600,  9602,  9608,  9610,
    9632,  9634,  9640,  9642,  11520, 11522, 11528, 11530, 11552, 11554, 11560,
    11562, 13440, 13442, 13448, 13450, 13472, 13474, 13480, 13482, 15360, 15362,
    15368, 15370, 15392, 15394, 15400, 15402, 17280, 17282, 17288, 17290, 17312,
    17314, 17320, 17322, 19200, 19202, 19208, 19210, 19232, 19234, 19240, 19242,
    21120, 21122, 21128, 21130, 21152, 21154, 21160, 21162, 23040, 23042, 23048,
    23050, 23072, 23074, 23080, 23082, 24960, 24962, 24968, 24970, 24992, 24994,
    25000, 25002, 26880, 26882, 26888, 26890, 26912, 26914, 26920, 26922, 28800,
    28802, 28808, 28810, 28832, 28834, 28840, 28842, 30720, 30722, 30728, 30730,
    30752, 30754, 30760, 30762, 32640, 32642, 32648, 32650, 32672, 32674, 32680,
    32682, 34560, 34562, 34568, 34570, 34592, 34594, 34600, 34602, 36480, 36482,
    36488, 36490, 36512, 36514, 36520, 36522, 38400, 38402, 38408, 38410, 38432,
    38434, 38440, 38442, 40320, 40322, 40328, 40330, 40352, 40354, 40360, 40362,
    42240, 42242, 42248, 42250, 42272, 42274, 42280, 42282, 44160, 44162, 44168,
    44170, 44192, 44194, 44200, 44202, 46080, 46082, 46088, 46090, 46112, 46114,
    46120, 46122, 48000, 48002, 48008, 48010, 48032, 48034, 48040, 48042, 49920,
    49922, 49928, 49930, 49952, 49954, 49960, 49962, 51840, 51842, 51848, 51850,
    51872, 51874, 51880, 51882, 53760, 53762, 53768, 53770, 53792, 53794, 53800,
    53802, 55680, 55682, 55688, 55690, 55712, 55714, 55720, 55722, 57600, 57602,
    57608, 57610, 57632, 57634, 57640, 57642, 59520, 59522, 59528, 59530, 59552,
    59554, 59560, 59562, 61440, 61442, 61448, 61450, 61472, 61474, 61480, 61482,
    63360, 63362, 63368, 63370, 63392, 63394, 63400, 63402, 65280, 65282, 65288,
    65290, 65312, 65314, 65320, 65322, 67200, 67202, 67208, 67210, 67232, 67234,
    67240, 67242, 69120, 69122, 69128, 69130, 69152, 69154, 69160, 69162, 71040,
    71042, 71048, 71050, 71072, 71074, 71080, 71082, 72960, 72962, 72968, 72970,
    72992, 72994, 73000, 73002, 74880, 74882, 74888, 74890, 74912, 74914, 74920,
    74922};

int _3ds_gl_framebuffer_offsets_y[] = {
    1877, 1876, 1873, 1872, 1861, 1860, 1857, 1856, 1813, 1812, 1809, 1808,
    1797, 1796, 1793, 1792, 1749, 1748, 1745, 1744, 1733, 1732, 1729, 1728,
    1685, 1684, 1681, 1680, 1669, 1668, 1665, 1664, 1621, 1620, 1617, 1616,
    1605, 1604, 1601, 1600, 1557, 1556, 1553, 1552, 1541, 1540, 1537, 1536,
    1493, 1492, 1489, 1488, 1477, 1476, 1473, 1472, 1429, 1428, 1425, 1424,
    1413, 1412, 1409, 1408, 1365, 1364, 1361, 1360, 1349, 1348, 1345, 1344,
    1301, 1300, 1297, 1296, 1285, 1284, 1281, 1280, 1237, 1236, 1233, 1232,
    1221, 1220, 1217, 1216, 1173, 1172, 1169, 1168, 1157, 1156, 1153, 1152,
    1109, 1108, 1105, 1104, 1093, 1092, 1089, 1088, 1045, 1044, 1041, 1040,
    1029, 1028, 1025, 1024, 981,  980,  977,  976,  965,  964,  961,  960,
    917,  916,  913,  912,  901,  900,  897,  896,  853,  852,  849,  848,
    837,  836,  833,  832,  789,  788,  785,  784,  773,  772,  769,  768,
    725,  724,  721,  720,  709,  708,  705,  704,  661,  660,  657,  656,
    645,  644,  641,  640,  597,  596,  593,  592,  581,  580,  577,  576,
    533,  532,  529,  528,  517,  516,  513,  512,  469,  468,  465,  464,
    453,  452,  449,  448,  405,  404,  401,  400,  389,  388,  385,  384,
    341,  340,  337,  336,  325,  324,  321,  320,  277,  276,  273,  272,
    261,  260,  257,  256,  213,  212,  209,  208,  197,  196,  193,  192,
    149,  148,  145,  144,  133,  132,  129,  128,  85,   84,   81,   80,
    69,   68,   65,   64,   21,   20,   17,   16,   5,    4,    1,    0};
#endif

void strtrim(char *s) {
    char *p = s;
    int l = strlen(p);

    while (isspace(p[l - 1])) {
        p[--l] = 0;
    }

    while (*p && isspace(*p)) {
        ++p;
        --l;
    }

    memmove(s, p, l + 1);
}

void strtolower(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}

int get_unsigned_byte(int8_t i) { return i & 0xff; }

int get_unsigned_short(int8_t *buffer, int offset) {
    return ((buffer[offset] & 0xff) << 8) + (buffer[offset + 1] & 0xff);
}

int get_unsigned_int(int8_t *buffer, int offset) {
    return ((buffer[offset] & 0xff) << 24) +
           ((buffer[offset + 1] & 0xff) << 16) +
           ((buffer[offset + 2] & 0xff) << 8) + (buffer[offset + 3] & 0xff);
}

int64_t get_unsigned_long(int8_t *buffer, int offset) {
    return (((int64_t)get_unsigned_int(buffer, offset) & 0xffffffff) << 32) +
           ((int64_t)get_unsigned_int(buffer, offset + 4) & 0xffffffff);
}

int get_signed_short(int8_t *buffer, int offset) {
    int i = get_unsigned_byte(buffer[offset]) * 256 +
            get_unsigned_byte(buffer[offset + 1]);

    if (i > 32767) {
        i -= 0x10000;
    }

    return i;
}

/* used for inventory and bank items, since most of the time there's less than
 * 128 */
int get_stack_int(int8_t *buffer, int offset) {
    if ((buffer[offset] & 0xff) < 128) {
        return buffer[offset];
    }

    return (((buffer[offset] & 0xff) - 128) << 24) +
           ((buffer[offset + 1] & 0xff) << 16) +
           ((buffer[offset + 2] & 0xff) << 8) + (buffer[offset + 3] & 0xff);
}

int get_bit_mask(int8_t *buffer, int offset, int length) {
    int byte_offset = offset >> 3;
    int bit_offset = 8 - (offset & 7);
    int bits = 0;

    for (; length > bit_offset; bit_offset = 8) {
        bits += (buffer[byte_offset++] & BITMASK[bit_offset])
                << (length - bit_offset);

        length -= bit_offset;
    }

    if (length == bit_offset) {
        bits += buffer[byte_offset] & BITMASK[bit_offset];
    } else {
        bits +=
            (buffer[byte_offset] >> (bit_offset - length)) & BITMASK[length];
    }

    return bits;
}

void write_unsigned_int(int8_t *buffer, int index, int i) {
    buffer[index] = (int8_t)(i >> 24);
    buffer[index + 1] = (int8_t)(i >> 16);
    buffer[index + 2] = (int8_t)(i >> 8);
    buffer[index + 3] = (int8_t)i;
}

void format_auth_string(char *raw, int max_length, char *formatted) {
    int raw_length = strlen(raw);

    for (int i = 0; i < max_length; i++) {
        char char_code = raw[i];

        if (i >= raw_length) {
            formatted[i] = ' ';
        } else if ((char_code >= 'a' && char_code <= 'z') ||
                   (char_code >= 'A' && char_code <= 'Z') ||
                   (char_code >= '0' && char_code <= '9')) {
            formatted[i] = char_code;
        } else {
            formatted[i] = '_';
        }
    }

    formatted[max_length] = '\0';
}

void ip_to_string(int32_t ip, char *ip_string) {
    sprintf(ip_string, "%d.%d.%d.%d", (ip >> 24) & 0xff, (ip >> 16) & 0xff,
            (ip >> 8) & 0xff, ip & 0xff);
}

int64_t encode_username(char *username) {
    int username_length = strlen(username);
    char cleaned[username_length + 1];

    for (int i = 0; i < username_length; i++) {
        char char_code = username[i];

        if ((char_code >= 'a' && char_code <= 'z') ||
            (char_code >= '0' && char_code <= '9')) {
            cleaned[i] = char_code;
        } else if (char_code >= 'A' && char_code <= 'Z') {
            cleaned[i] = char_code + 97 - 65;
        } else {
            cleaned[i] = ' ';
        }
    }

    cleaned[username_length] = '\0';

    strtrim(cleaned);

    int cleaned_length = strlen(cleaned);

    if (cleaned_length > MAX_USER_LENGTH) {
        cleaned[MAX_USER_LENGTH + 1] = '\0';
        cleaned_length = MAX_USER_LENGTH;
    }

    int64_t encoded = 0;

    for (int i = 0; i < cleaned_length; i++) {
        char char_code = cleaned[i];

        encoded *= 37;

        if (char_code >= 'a' && char_code <= 'z') {
            encoded += 1 + char_code - 97;
        } else if (char_code >= '0' && char_code <= '9') {
            encoded += 27 + char_code - 48;
        }
    }

    return encoded;
}

void decode_username(int64_t encoded, char *decoded) {
    if (encoded < 0) {
        strcpy(decoded, "invalidName");
    }

    int length = 0;

    while (encoded != 0) {
        char char_code = (encoded % 37);
        encoded /= 37;

        if (char_code == 0) {
            decoded[length++] = ' ';
        } else if (char_code < 27) {
            if (encoded % 37 == 0) {
                decoded[length++] = (char_code + 65 - 1);
            } else {
                decoded[length++] = (char_code + 97 - 1);
            }
        } else {
            decoded[length++] = (char_code + 48 - 27);
        }
    }

    int end = length - 1;

    for (int i = 0; i < length / 2; i++) {
        char temp = decoded[i];
        decoded[i] = decoded[end];
        decoded[end] = temp;
        end--;
    }

    decoded[length++] = '\0';
}

static int32_t hash_file_name(char *file_name) {
    int i = 0;

    char upper_file_name[strlen(file_name) + 1];

    while (file_name[i]) {
        upper_file_name[i] = toupper(file_name[i]);
        i++;
    }

    file_name = upper_file_name;

    int file_name_length = i;
    int32_t hash = 0;

    for (int i = 0; i < file_name_length; i++) {
        hash = hash * 61 + file_name[i] - 32;
    }

    return hash;
}

static int32_t get_file_hash(int8_t *buffer, int entry) {
    return (buffer[entry * 10 + 2] & 0xff) * 0x1000000 +
           (buffer[entry * 10 + 3] & 0xff) * 0x10000 +
           (buffer[entry * 10 + 4] & 0xff) * 0x100 +
           (buffer[entry * 10 + 5] & 0xff);
}

static int get_file_size(int8_t *buffer, int entry) {
    return (buffer[entry * 10 + 6] & 0xff) * 0x10000 +
           (buffer[entry * 10 + 7] & 0xff) * 0x100 +
           (buffer[entry * 10 + 8] & 0xff);
}

static int get_archive_size(int8_t *buffer, int entry) {
    return (buffer[entry * 10 + 9] & 0xff) * 0x10000 +
           (buffer[entry * 10 + 10] & 0xff) * 0x100 +
           (buffer[entry * 10 + 11] & 0xff);
}

int get_data_file_offset(char *file_name, int8_t *buffer) {
    int num_entries = get_unsigned_short(buffer, 0);
    int32_t wanted_hash = hash_file_name(file_name);
    int offset = 2 + num_entries * 10;

    for (int entry = 0; entry < num_entries; entry++) {
        int32_t file_hash = get_file_hash(buffer, entry);
        int archive_size = get_archive_size(buffer, entry);

        if (file_hash == wanted_hash) {
            return offset;
        }

        offset += archive_size;
    }

    return 0;
}

int get_data_file_length(char *file_name, int8_t *buffer) {
    int num_entries = get_unsigned_short(buffer, 0);
    int32_t wanted_hash = hash_file_name(file_name);

    for (int entry = 0; entry < num_entries; entry++) {
        int32_t file_hash = get_file_hash(buffer, entry);
        int file_size = get_file_size(buffer, entry);

        if (file_hash == wanted_hash) {
            return file_size;
        }
    }

    return 0;
}

int8_t *unpack_data(char *file_name, int extra_size, int8_t *archive_data,
                    int8_t *file_data) {
    int num_entries = get_unsigned_short(archive_data, 0);
    int32_t wanted_hash = hash_file_name(file_name);
    int offset = 2 + num_entries * 10;

    for (int entry = 0; entry < num_entries; entry++) {
        int32_t file_hash = get_file_hash(archive_data, entry);
        int file_size = get_file_size(archive_data, entry);
        int archive_size = get_archive_size(archive_data, entry);

        if (file_hash == wanted_hash) {
            if (file_data == NULL) {
                file_data = malloc(file_size + extra_size);
            }

            if (file_size != archive_size) {
                bzip_decompress(file_data, file_size, archive_data,
                                archive_size, offset);
            } else {
                for (int i = 0; i < file_size; i++) {
                    file_data[i] = archive_data[offset + i];
                }
            }

            return file_data;
        }

        offset += archive_size;
    }

    return NULL;
}

int8_t *load_data(char *file_name, int extra_size, int8_t *archive_data) {
    if (archive_data == NULL) {
        return NULL;
    }

    return unpack_data(file_name, extra_size, archive_data, NULL);
}

void format_confirm_amount(int amount, char *formatted) {
    sprintf(formatted, "%d", amount);

    int formatted_length = strlen(formatted);

    for (int i = formatted_length - 3; i > 0; i -= 3) {
        int begin_length = i;
        char begin[begin_length + 1];
        begin[begin_length] = '\0';

        int end_length = formatted_length - i;
        char end[end_length + 1];
        end[end_length] = '\0';

        strncpy(begin, formatted, begin_length);
        strncpy(end, formatted + i, end_length);

        sprintf(formatted, "%s,%s", begin, end);

        formatted_length = strlen(formatted);
    }

    if (formatted_length > 8) {
        int short_length = formatted_length - 8;
        char short_num[short_length + 1];
        short_num[short_length] = '\0';

        strncpy(short_num, formatted, short_length);

        char formatted_copy[formatted_length];
        strcpy(formatted_copy, formatted);

        sprintf(formatted, "@gre@%s million @whi@(%s)", short_num,
                formatted_copy);
    } else if (formatted_length > 4) {
        int short_length = formatted_length - 4;
        char short_num[short_length + 1];
        short_num[short_length] = '\0';

        strncpy(short_num, formatted, short_length);

        char formatted_copy[formatted_length];
        strcpy(formatted_copy, formatted);

        sprintf(formatted, "@cya@%s K @whi@(%s)", short_num, formatted_copy);
    }
}

int get_ticks() {
#if !defined(WII) && !defined(_3DS)
    return SDL_GetTicks();
#endif

#ifdef _3DS
    return (int)osGetTime();
    // return (int)(svcGetSystemTick() / CPU_TICKS_PER_MSEC);
#endif

#ifdef WII
    uint64_t ticks = gettime();
    return (int)(ticks / TB_TIMER_CLOCK);
#endif
}

void delay_ticks(int ticks) {
#if !defined(WII) && !defined(_3DS)
#ifdef EMSCRIPTEN
    emscripten_sleep(ticks);
#else
    SDL_Delay(ticks);
#endif
#endif

#ifdef _3DS
    svcSleepThread(ticks * 1000);
    /*int end = get_ticks() + ticks;

    while (get_ticks() != end)
        ;*/
#endif

#ifdef WII
    int end = get_ticks() + ticks;

    while (get_ticks() != end)
        ;
#endif
}

void get_level_difference_colour(int level_difference, char *colour) {
    if (level_difference < 0) {
        strcpy(colour, "@or1@");
    }

    if (level_difference < -3) {
        strcpy(colour, "@or2@");
    }

    if (level_difference < -6) {
        strcpy(colour, "@or3@");
    }

    if (level_difference < -9) {
        strcpy(colour, "@red@");
    }

    if (level_difference > 0) {
        strcpy(colour, "@gr1@");
    }

    if (level_difference > 3) {
        strcpy(colour, "@gr2@");
    }

    if (level_difference > 6) {
        strcpy(colour, "@gr3@");
    }

    if (level_difference > 9) {
        strcpy(colour, "@gre@");
    }
}

void ulaw_to_linear(long size, uint8_t *u_ptr, int16_t *out_ptr) {
    for (long i = 0; i < size; i++) {
        uint16_t u_val = ~(*u_ptr++);

        short t = ((u_val & QUANT_MASK) << 3) + BIAS;
        t <<= ((unsigned)u_val & SEG_MASK) >> SEG_SHIFT;

        *out_ptr++ = ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
    }
}

void format_number_commas(int number, char *dest) {
    if (number < 1000) {
        sprintf(dest, "%d", number);
    } else {
        format_number_commas(number / 1000, dest);
        sprintf(dest + strlen(dest), ",%03d", number % 1000);
    }
}

void format_amount_suffix(int amount, int use_colour, int convert_ten_thousands,
                          int use_commas, char *dest) {
    float scale = 1.0f;
    char colour[6] = {0};
    char suffix = '\0';

    if (amount >= 10000000) {
        scale = 1000000.0f;
        strcpy(colour, "@gre@");
        suffix = 'M';
    } else if (amount >= (convert_ten_thousands ? 10000 : 100000)) {
        scale = 1000.0f;
        strcpy(colour, "@whi@");
        suffix = 'K';
    }

    amount = floorf((float)amount / scale);

    char formatted_amount[15] = {0};

    if (use_commas) {
        format_number_commas(amount, formatted_amount);
    } else {
        sprintf(formatted_amount, "%d", amount);
    }

    sprintf(dest, "%s%s%c", use_colour ? colour : "", formatted_amount, suffix);
}

void url_encode(char *s, char *dest) {
    const char *hex = "0123456789abcdef";

    int pos = 0;
    int length = strlen(s);

    for (int i = 0; i < length; i++) {
        if (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z') ||
            ('0' <= s[i] && s[i] <= '9')) {
            dest[pos++] = s[i];
        } else {
            dest[pos++] = '%';
            dest[pos++] = hex[s[i] >> 4];
            dest[pos++] = hex[s[i] & 15];
        }
    }

    dest[pos] = '\0';
}

int get_certificate_item_id(int item_id) {
    int length = sizeof(certificate_items) / sizeof(certificate_items[0]);

    for (int i = 0; i < length; i++) {
        if (certificate_items[i][0] == item_id) {
            return certificate_items[i][1];
        }
    }

    return -1;
}

#if defined(RENDER_GL) || defined(RENDER_3DS_GL)
float gl_translate_coord(int position, int range) {
    float half = range / 2.0f;
    return (position - half) / half;
}
#endif

#ifdef RENDER_GL
float gl_translate_x(int x, int range) { return gl_translate_coord(x, range); }

float gl_translate_y(int y, int range) { return -gl_translate_coord(y, range); }

void gl_load_texture(GLuint *texture_id, char *file) {
    glGenTextures(1, texture_id);
    glBindTexture(GL_TEXTURE_2D, *texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    SDL_Surface *texture_image = IMG_Load(file);

    if (!texture_image) {
        fprintf(stderr, "unable to load %s texture\n", file);
        fprintf(stderr, "%s\n", IMG_GetError());
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_image->w, texture_image->h,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image->pixels);
}

// TODO gl_
void rotate_point(int centre_x, int centre_y, float angle, int *point) {
    point[0] -= centre_x;
    point[1] -= centre_y;

    float sine = sin(angle);
    float cosine = cos(angle);

    int x_new = point[0] * cosine - point[1] * sine;
    int y_new = point[0] * sine + point[1] * cosine;

    point[0] = x_new + centre_x;
    point[1] = y_new + centre_y;
}
#elif defined(RENDER_3DS_GL)
float gl_translate_x(int x, int range) {
    (void)range;
    return x;
}

float gl_translate_y(int y, int range) { return range - y; }

void _3ds_gl_load_tex(const uint8_t *t3x_data, size_t t3x_size, C3D_Tex *tex) {
    Tex3DS_Texture t3x =
        Tex3DS_TextureImport(t3x_data, t3x_size, tex, NULL, false);

    Tex3DS_TextureFree(t3x);

    C3D_TexSetFilter(tex, GPU_NEAREST, GPU_NEAREST);
}

/* translate (y * width) + index into internal framebuffer index */
int _3ds_gl_translate_framebuffer_index(int index) {
    int y_offset = floor(index / 320);
    int x_offset = index - (y_offset * 320);

    return _3ds_gl_framebuffer_offsets_x[x_offset] +
           _3ds_gl_framebuffer_offsets_y[y_offset];
}
#endif
