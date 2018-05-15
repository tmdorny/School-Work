from hpdf import *

__version__='2.0.8'

__all__=[
'HPDF_ANNOT_CIRCLE',  'HPDF_ANNOT_DOWN_APPEARANCE',  'HPDF_ANNOT_FILE_ATTACHMENT',  'HPDF_ANNOT_FREE_TEXT',  'HPDF_ANNOT_HIDDEN',  'HPDF_ANNOT_HIGHTLIGHT',  'HPDF_ANNOT_HIGHTLIGHT_MODE_EOF',  'HPDF_ANNOT_ICON_COMMENT',  'HPDF_ANNOT_ICON_EOF',  'HPDF_ANNOT_ICON_HELP',  'HPDF_ANNOT_ICON_INSERT',  'HPDF_ANNOT_ICON_KEY',  'HPDF_ANNOT_ICON_NEW_PARAGRAPH',  'HPDF_ANNOT_ICON_NOTE',  'HPDF_ANNOT_ICON_PARAGRAPH',  'HPDF_ANNOT_INK',  'HPDF_ANNOT_INVERT_BORDER',  'HPDF_ANNOT_INVERT_BOX',  'HPDF_ANNOT_INVISIBLE',  'HPDF_ANNOT_LINK',  'HPDF_ANNOT_NOROTATE',  'HPDF_ANNOT_NOVIEW',  'HPDF_ANNOT_NOZOOM',  'HPDF_ANNOT_NO_HIGHTLIGHT',  'HPDF_ANNOT_POPUP',  'HPDF_ANNOT_PRINT',  'HPDF_ANNOT_READONLY',  'HPDF_ANNOT_SOUND',  'HPDF_ANNOT_SQUARE',  'HPDF_ANNOT_STAMP',  'HPDF_ANNOT_STRIKE_OUT',  'HPDF_ANNOT_TEXT_NOTES',  'HPDF_ANNOT_UNDERLINE',  'HPDF_AddPage',  'HPDF_AddPageLabel',  'HPDF_Alloc_Func',  'HPDF_AnnotFlgs',  'HPDF_AnnotHighlightMode',  'HPDF_AnnotIcon',  'HPDF_AnnotType',  'HPDF_Annotation',  'HPDF_BEVEL_JOIN',  'HPDF_BM_COLOR_BUM',  'HPDF_BM_COLOR_DODGE',  'HPDF_BM_DARKEN',  'HPDF_BM_DIFFERENCE',  'HPDF_BM_EOF',  'HPDF_BM_EXCLUSHON',  'HPDF_BM_HARD_LIGHT',  'HPDF_BM_LIGHTEN',  'HPDF_BM_MULTIPLY',  'HPDF_BM_NORMAL',  'HPDF_BM_OVERLAY',  'HPDF_BM_SCREEN',  'HPDF_BM_SOFT_LIGHT',  'HPDF_BOOL',  'HPDF_BSSubtype',  'HPDF_BS_BEVELED',  'HPDF_BS_DASHED',  'HPDF_BS_DEF_WIDTH',  'HPDF_BS_INSET',  'HPDF_BS_SOLID',  'HPDF_BS_UNDERLINED',  'HPDF_BUTT_END',  'HPDF_BYTE',  'HPDF_BYTE_OFFSET_LEN',  'HPDF_BYTE_TYPE_LEAD',  'HPDF_BYTE_TYPE_SINGLE',  'HPDF_BYTE_TYPE_TRIAL',  'HPDF_BYTE_TYPE_UNKNOWN',  'HPDF_BlendMode',  'HPDF_Box',  'HPDF_ByteType',  'HPDF_CENTER_WINDOW',  'HPDF_CID',  'HPDF_CLIPPING',  'HPDF_CMYKColor',  'HPDF_COMP_ALL',  'HPDF_COMP_BEST_COMPRESS',  'HPDF_COMP_BEST_SPEED',  'HPDF_COMP_IMAGE',  'HPDF_COMP_MASK',  'HPDF_COMP_METADATA',  'HPDF_COMP_NONE',  'HPDF_COMP_TEXT',  'HPDF_COUNTRY_AD',  'HPDF_COUNTRY_AE',  'HPDF_COUNTRY_AF',  'HPDF_COUNTRY_AG',  'HPDF_COUNTRY_AI',  'HPDF_COUNTRY_AL',  'HPDF_COUNTRY_AM',  'HPDF_COUNTRY_AN',  'HPDF_COUNTRY_AO',  'HPDF_COUNTRY_AQ',  'HPDF_COUNTRY_AR',  'HPDF_COUNTRY_AS',  'HPDF_COUNTRY_AT',  'HPDF_COUNTRY_AU',  'HPDF_COUNTRY_AW',  'HPDF_COUNTRY_AZ',  'HPDF_COUNTRY_BA',  'HPDF_COUNTRY_BB',  'HPDF_COUNTRY_BD',  'HPDF_COUNTRY_BE',  'HPDF_COUNTRY_BF',  'HPDF_COUNTRY_BG',  'HPDF_COUNTRY_BH',  'HPDF_COUNTRY_BI',  'HPDF_COUNTRY_BJ',  'HPDF_COUNTRY_BM',  'HPDF_COUNTRY_BN',  'HPDF_COUNTRY_BO',  'HPDF_COUNTRY_BR',  'HPDF_COUNTRY_BS',  'HPDF_COUNTRY_BT',  'HPDF_COUNTRY_BV',  'HPDF_COUNTRY_BW',  'HPDF_COUNTRY_BY',  'HPDF_COUNTRY_BZ',  'HPDF_COUNTRY_CA',  'HPDF_COUNTRY_CC',  'HPDF_COUNTRY_CF',  'HPDF_COUNTRY_CG',  'HPDF_COUNTRY_CH',  'HPDF_COUNTRY_CI',  'HPDF_COUNTRY_CK',  'HPDF_COUNTRY_CL',  'HPDF_COUNTRY_CM',  'HPDF_COUNTRY_CN',  'HPDF_COUNTRY_CO',  'HPDF_COUNTRY_CR',  'HPDF_COUNTRY_CU',  'HPDF_COUNTRY_CV',  'HPDF_COUNTRY_CX',  'HPDF_COUNTRY_CY',  'HPDF_COUNTRY_CZ',  'HPDF_COUNTRY_DE',  'HPDF_COUNTRY_DJ',  'HPDF_COUNTRY_DK',  'HPDF_COUNTRY_DM',  'HPDF_COUNTRY_DO',  'HPDF_COUNTRY_DZ',  'HPDF_COUNTRY_EC',  'HPDF_COUNTRY_EE',  'HPDF_COUNTRY_EG',  'HPDF_COUNTRY_EH',  'HPDF_COUNTRY_ER',  'HPDF_COUNTRY_ES',  'HPDF_COUNTRY_ET',  'HPDF_COUNTRY_FI',  'HPDF_COUNTRY_FJ',  'HPDF_COUNTRY_FK',  'HPDF_COUNTRY_FM',  'HPDF_COUNTRY_FO',  'HPDF_COUNTRY_FR',  'HPDF_COUNTRY_FX',  'HPDF_COUNTRY_GA',  'HPDF_COUNTRY_GB',  'HPDF_COUNTRY_GD',  'HPDF_COUNTRY_GE',  'HPDF_COUNTRY_GF',  'HPDF_COUNTRY_GH',  'HPDF_COUNTRY_GI',  'HPDF_COUNTRY_GL',  'HPDF_COUNTRY_GM',  'HPDF_COUNTRY_GN',  'HPDF_COUNTRY_GP',  'HPDF_COUNTRY_GQ',  'HPDF_COUNTRY_GR',  'HPDF_COUNTRY_GT',  'HPDF_COUNTRY_GU',  'HPDF_COUNTRY_GW',  'HPDF_COUNTRY_GY',  'HPDF_COUNTRY_HK',  'HPDF_COUNTRY_HM',  'HPDF_COUNTRY_HN',  'HPDF_COUNTRY_HR',  'HPDF_COUNTRY_HT',  'HPDF_COUNTRY_HU',  'HPDF_COUNTRY_ID',  'HPDF_COUNTRY_IE',  'HPDF_COUNTRY_IL',  'HPDF_COUNTRY_IN',  'HPDF_COUNTRY_IO',  'HPDF_COUNTRY_IQ',  'HPDF_COUNTRY_IR',  'HPDF_COUNTRY_IS',  'HPDF_COUNTRY_IT',  'HPDF_COUNTRY_JM',  'HPDF_COUNTRY_JO',  'HPDF_COUNTRY_JP',  'HPDF_COUNTRY_KE',  'HPDF_COUNTRY_KG',  'HPDF_COUNTRY_KH',  'HPDF_COUNTRY_KI',  'HPDF_COUNTRY_KM',  'HPDF_COUNTRY_KN',  'HPDF_COUNTRY_KP',  'HPDF_COUNTRY_KR',  'HPDF_COUNTRY_KW',  'HPDF_COUNTRY_KY',  'HPDF_COUNTRY_KZ',  'HPDF_COUNTRY_LA',  'HPDF_COUNTRY_LB',  'HPDF_COUNTRY_LC',  'HPDF_COUNTRY_LI',  'HPDF_COUNTRY_LK',  'HPDF_COUNTRY_LR',  'HPDF_COUNTRY_LS',  'HPDF_COUNTRY_LT',  'HPDF_COUNTRY_LU',  'HPDF_COUNTRY_LV',  'HPDF_COUNTRY_LY',  'HPDF_COUNTRY_MA',  'HPDF_COUNTRY_MC',  'HPDF_COUNTRY_MD',  'HPDF_COUNTRY_MG',  'HPDF_COUNTRY_MH',  'HPDF_COUNTRY_MK',  'HPDF_COUNTRY_ML',  'HPDF_COUNTRY_MM',  'HPDF_COUNTRY_MN',  'HPDF_COUNTRY_MO',  'HPDF_COUNTRY_MP',  'HPDF_COUNTRY_MQ',  'HPDF_COUNTRY_MR',  'HPDF_COUNTRY_MS',  'HPDF_COUNTRY_MT',  'HPDF_COUNTRY_MU',  'HPDF_COUNTRY_MV',  'HPDF_COUNTRY_MW',  'HPDF_COUNTRY_MX',  'HPDF_COUNTRY_MY',  'HPDF_COUNTRY_MZ',  'HPDF_COUNTRY_NA',  'HPDF_COUNTRY_NC',  'HPDF_COUNTRY_NE',  'HPDF_COUNTRY_NF',  'HPDF_COUNTRY_NG',  'HPDF_COUNTRY_NI',  'HPDF_COUNTRY_NL',  'HPDF_COUNTRY_NO',  'HPDF_COUNTRY_NP',  'HPDF_COUNTRY_NR',  'HPDF_COUNTRY_NU',  'HPDF_COUNTRY_NZ',  'HPDF_COUNTRY_OM',  'HPDF_COUNTRY_PA',  'HPDF_COUNTRY_PE',  'HPDF_COUNTRY_PF',  'HPDF_COUNTRY_PG',  'HPDF_COUNTRY_PH',  'HPDF_COUNTRY_PK',  'HPDF_COUNTRY_PL',  'HPDF_COUNTRY_PM',  'HPDF_COUNTRY_PN',  'HPDF_COUNTRY_PR',  'HPDF_COUNTRY_PT',  'HPDF_COUNTRY_PW',  'HPDF_COUNTRY_PY',  'HPDF_COUNTRY_QA',  'HPDF_COUNTRY_RE',  'HPDF_COUNTRY_RO',  'HPDF_COUNTRY_RU',  'HPDF_COUNTRY_RW',  'HPDF_COUNTRY_SA',  'HPDF_COUNTRY_SB',  'HPDF_COUNTRY_SC',  'HPDF_COUNTRY_SD',  'HPDF_COUNTRY_SE',  'HPDF_COUNTRY_SG',  'HPDF_COUNTRY_SH',  'HPDF_COUNTRY_SI',  'HPDF_COUNTRY_SJ',  'HPDF_COUNTRY_SK',  'HPDF_COUNTRY_SL',  'HPDF_COUNTRY_SM',  'HPDF_COUNTRY_SN',  'HPDF_COUNTRY_SO',  'HPDF_COUNTRY_SR',  'HPDF_COUNTRY_ST',  'HPDF_COUNTRY_SV',  'HPDF_COUNTRY_SY',  'HPDF_COUNTRY_SZ',  'HPDF_COUNTRY_TC',  'HPDF_COUNTRY_TD',  'HPDF_COUNTRY_TF',  'HPDF_COUNTRY_TG',  'HPDF_COUNTRY_TH',  'HPDF_COUNTRY_TJ',  'HPDF_COUNTRY_TK',  'HPDF_COUNTRY_TM',  'HPDF_COUNTRY_TN',  'HPDF_COUNTRY_TO',  'HPDF_COUNTRY_TP',  'HPDF_COUNTRY_TR',  'HPDF_COUNTRY_TT',  'HPDF_COUNTRY_TV',  'HPDF_COUNTRY_TW',  'HPDF_COUNTRY_TZ',  'HPDF_COUNTRY_UA',  'HPDF_COUNTRY_UG',  'HPDF_COUNTRY_UM',  'HPDF_COUNTRY_US',  'HPDF_COUNTRY_UY',  'HPDF_COUNTRY_UZ',  'HPDF_COUNTRY_VA',  'HPDF_COUNTRY_VC',  'HPDF_COUNTRY_VE',  'HPDF_COUNTRY_VG',  'HPDF_COUNTRY_VI',  'HPDF_COUNTRY_VN',  'HPDF_COUNTRY_VU',  'HPDF_COUNTRY_WF',  'HPDF_COUNTRY_WS',  'HPDF_COUNTRY_YE',  'HPDF_COUNTRY_YT',  'HPDF_COUNTRY_YU',  'HPDF_COUNTRY_ZA',  'HPDF_COUNTRY_ZM',  'HPDF_COUNTRY_ZR',  'HPDF_COUNTRY_ZW',  'HPDF_CS_CAL_GRAY',  'HPDF_CS_CAL_RGB',  'HPDF_CS_DEVICE_CMYK',  'HPDF_CS_DEVICE_GRAY',  'HPDF_CS_DEVICE_N',  'HPDF_CS_DEVICE_RGB',  'HPDF_CS_EOF',  'HPDF_CS_ICC_BASED',  'HPDF_CS_INDEXED',  'HPDF_CS_LAB',  'HPDF_CS_PATTERN',  'HPDF_CS_SEPARATION',  'HPDF_ColorSpace',  'HPDF_CreateExtGState',  'HPDF_CreateOutline',  'HPDF_DATE_TIME_STR_LEN',  'HPDF_DEF_CHARSPACE',  'HPDF_DEF_FLATNESS',  'HPDF_DEF_FONT',  'HPDF_DEF_FONTSIZE',  'HPDF_DEF_HSCALING',  'HPDF_DEF_LEADING',  'HPDF_DEF_LINECAP',  'HPDF_DEF_LINEJOIN',  'HPDF_DEF_LINEWIDTH',  'HPDF_DEF_MITERLIMIT',  'HPDF_DEF_PAGE_HEIGHT',  'HPDF_DEF_PAGE_LAYOUT',  'HPDF_DEF_PAGE_MODE',  'HPDF_DEF_PAGE_NUM',  'HPDF_DEF_PAGE_WIDTH',  'HPDF_DEF_RAISE',  'HPDF_DEF_RENDERING_MODE',  'HPDF_DEF_RISE',  'HPDF_DEF_WORDSPACE',  'HPDF_DOUBLE',  'HPDF_DST_EOF',  'HPDF_DashMode',  'HPDF_Date',  'HPDF_Destination',  'HPDF_DestinationType',  'HPDF_Destination_SetFit',  'HPDF_Destination_SetFitB',  'HPDF_Destination_SetFitBH',  'HPDF_Destination_SetFitBV',  'HPDF_Destination_SetFitH',  'HPDF_Destination_SetFitR',  'HPDF_Destination_SetFitV',  'HPDF_Destination_SetXYZ',  'HPDF_Doc',  'HPDF_ENABLE_COPY',  'HPDF_ENABLE_EDIT',  'HPDF_ENABLE_EDIT_ALL',  'HPDF_ENABLE_PRINT',  'HPDF_ENABLE_READ',  'HPDF_ENCODER_TYPE_DOUBLE_BYTE',  'HPDF_ENCODER_TYPE_SINGLE_BYTE',  'HPDF_ENCODER_TYPE_UNINITIALIZED',  'HPDF_ENCODER_UNKNOWN',  'HPDF_ENCRYPT_R2',  'HPDF_ENCRYPT_R3',  'HPDF_Encoder',  'HPDF_EncoderType',  'HPDF_Encoder_GetByteType',  'HPDF_Encoder_GetType',  'HPDF_Encoder_GetUnicode',  'HPDF_Encoder_GetWritingMode',  'HPDF_EncryptMode',  'HPDF_Error_Handler',  'HPDF_ExtGState',  'HPDF_ExtGState_SetAlphaFill',  'HPDF_ExtGState_SetAlphaStroke',  'HPDF_ExtGState_SetBlendMode',  'HPDF_FALSE',  'HPDF_FILL',  'HPDF_FILL_CLIPPING',  'HPDF_FILL_STROKE_CLIPPING',  'HPDF_FILL_THEN_STROKE',  'HPDF_FIT',  'HPDF_FIT_B',  'HPDF_FIT_BH',  'HPDF_FIT_BV',  'HPDF_FIT_H',  'HPDF_FIT_R',  'HPDF_FIT_V',  'HPDF_FIT_WINDOW',  'HPDF_Font',  'HPDF_Font_GetAscent',  'HPDF_Font_GetBBox',  'HPDF_Font_GetCapHeight',  'HPDF_Font_GetDescent',  'HPDF_Font_GetEncodingName',  'HPDF_Font_GetFontName',  'HPDF_Font_GetUnicodeWidth',  'HPDF_Font_GetXHeight',  'HPDF_Font_MeasureText',  'HPDF_Font_TextWidth',  'HPDF_Free',  'HPDF_FreeDoc',  'HPDF_FreeDocAll',  'HPDF_Free_Func',  'HPDF_GEN_NO_LEN',  'HPDF_GMODE_CLIPPING_PATH',  'HPDF_GMODE_EXTERNAL_OBJECT',  'HPDF_GMODE_INLINE_IMAGE',  'HPDF_GMODE_PAGE_DESCRIPTION',  'HPDF_GMODE_PATH_OBJECT',  'HPDF_GMODE_SHADING',  'HPDF_GMODE_TEXT_OBJECT',  'HPDF_GetCurrentEncoder',  'HPDF_GetCurrentPage',  'HPDF_GetEncoder',  'HPDF_GetError',  'HPDF_GetErrorDetail',  'HPDF_GetFont',  'HPDF_GetInfoAttr',  'HPDF_GetPageByIndex',  'HPDF_GetPageLayout',  'HPDF_GetPageMode',  'HPDF_GetStreamSize',  'HPDF_GetVersion',  'HPDF_GetViewerPreference',  'HPDF_HANDLE',  'HPDF_HIDE_MENUBAR',  'HPDF_HIDE_TOOLBAR',  'HPDF_HIDE_WINDOW_UI',  'HPDF_HasDoc',  'HPDF_INFO_AUTHOR',  'HPDF_INFO_CREATION_DATE',  'HPDF_INFO_CREATOR',  'HPDF_INFO_EOF',  'HPDF_INFO_KEYWORDS',  'HPDF_INFO_MOD_DATE',  'HPDF_INFO_PRODUCER',  'HPDF_INFO_SUBJECT',  'HPDF_INFO_TITLE',  'HPDF_INT',  'HPDF_INT16',  'HPDF_INT32',  'HPDF_INT8',  'HPDF_INT_LEN',  'HPDF_INVISIBLE',  'HPDF_Image',  'HPDF_Image_GetBitsPerComponent',  'HPDF_Image_GetColorSpace',  'HPDF_Image_GetHeight',  'HPDF_Image_GetSize',  'HPDF_Image_GetSize2',  'HPDF_Image_GetWidth',  'HPDF_Image_SetColorMask',  'HPDF_Image_SetMaskImage',  'HPDF_InfoType',  'HPDF_InsertPage',  'HPDF_LANG_AA',  'HPDF_LANG_AB',  'HPDF_LANG_AF',  'HPDF_LANG_AM',  'HPDF_LANG_AR',  'HPDF_LANG_AS',  'HPDF_LANG_AY',  'HPDF_LANG_AZ',  'HPDF_LANG_BA',  'HPDF_LANG_BE',  'HPDF_LANG_BG',  'HPDF_LANG_BH',  'HPDF_LANG_BI',  'HPDF_LANG_BN',  'HPDF_LANG_BO',  'HPDF_LANG_BR',  'HPDF_LANG_CA',  'HPDF_LANG_CO',  'HPDF_LANG_CS',  'HPDF_LANG_CY',  'HPDF_LANG_DA',  'HPDF_LANG_DE',  'HPDF_LANG_DZ',  'HPDF_LANG_EL',  'HPDF_LANG_EN',  'HPDF_LANG_EO',  'HPDF_LANG_ES',  'HPDF_LANG_ET',  'HPDF_LANG_EU',  'HPDF_LANG_FA',  'HPDF_LANG_FI',  'HPDF_LANG_FJ',  'HPDF_LANG_FO',  'HPDF_LANG_FR',  'HPDF_LANG_FY',  'HPDF_LANG_GA',  'HPDF_LANG_GD',  'HPDF_LANG_GL',  'HPDF_LANG_GN',  'HPDF_LANG_GU',  'HPDF_LANG_HA',  'HPDF_LANG_HI',  'HPDF_LANG_HR',  'HPDF_LANG_HU',  'HPDF_LANG_HY',  'HPDF_LANG_IA',  'HPDF_LANG_IE',  'HPDF_LANG_IK',  'HPDF_LANG_IN',  'HPDF_LANG_IS',  'HPDF_LANG_IT',  'HPDF_LANG_IW',  'HPDF_LANG_JA',  'HPDF_LANG_JI',  'HPDF_LANG_JW',  'HPDF_LANG_KA',  'HPDF_LANG_KK',  'HPDF_LANG_KL',  'HPDF_LANG_KM',  'HPDF_LANG_KN',  'HPDF_LANG_KO',  'HPDF_LANG_KS',  'HPDF_LANG_KU',  'HPDF_LANG_KY',  'HPDF_LANG_LA',  'HPDF_LANG_LN',  'HPDF_LANG_LO',  'HPDF_LANG_LT',  'HPDF_LANG_LV',  'HPDF_LANG_MG',  'HPDF_LANG_MI',  'HPDF_LANG_MK',  'HPDF_LANG_ML',  'HPDF_LANG_MN',  'HPDF_LANG_MO',  'HPDF_LANG_MR',  'HPDF_LANG_MS',  'HPDF_LANG_MT',  'HPDF_LANG_MY',  'HPDF_LANG_NA',  'HPDF_LANG_NE',  'HPDF_LANG_NL',  'HPDF_LANG_NO',  'HPDF_LANG_OC',  'HPDF_LANG_OM',  'HPDF_LANG_OR',  'HPDF_LANG_PA',  'HPDF_LANG_PL',  'HPDF_LANG_PS',  'HPDF_LANG_PT',  'HPDF_LANG_QU',  'HPDF_LANG_RM',  'HPDF_LANG_RN',  'HPDF_LANG_RO',  'HPDF_LANG_RU',  'HPDF_LANG_RW',  'HPDF_LANG_SA',  'HPDF_LANG_SD',  'HPDF_LANG_SG',  'HPDF_LANG_SH',  'HPDF_LANG_SI',  'HPDF_LANG_SK',  'HPDF_LANG_SL',  'HPDF_LANG_SM',  'HPDF_LANG_SN',  'HPDF_LANG_SO',  'HPDF_LANG_SQ',  'HPDF_LANG_SR',  'HPDF_LANG_SS',  'HPDF_LANG_ST',  'HPDF_LANG_SU',  'HPDF_LANG_SV',  'HPDF_LANG_SW',  'HPDF_LANG_TA',  'HPDF_LANG_TE',  'HPDF_LANG_TG',  'HPDF_LANG_TH',  'HPDF_LANG_TI',  'HPDF_LANG_TK',  'HPDF_LANG_TL',  'HPDF_LANG_TN',  'HPDF_LANG_TR',  'HPDF_LANG_TS',  'HPDF_LANG_TT',  'HPDF_LANG_TW',  'HPDF_LANG_UK',  'HPDF_LANG_UR',  'HPDF_LANG_UZ',  'HPDF_LANG_VI',  'HPDF_LANG_VO',  'HPDF_LANG_WO',  'HPDF_LANG_XH',  'HPDF_LANG_YO',  'HPDF_LANG_ZH',  'HPDF_LANG_ZU',  'HPDF_LIMIT_MAX_ARRAY',  'HPDF_LIMIT_MAX_CID',  'HPDF_LIMIT_MAX_DEVICE_N',  'HPDF_LIMIT_MAX_DEVICE_N_V15',  'HPDF_LIMIT_MAX_DICT_ELEMENT',  'HPDF_LIMIT_MAX_GSTATE',  'HPDF_LIMIT_MAX_INT',  'HPDF_LIMIT_MAX_NAME_LEN',  'HPDF_LIMIT_MAX_REAL',  'HPDF_LIMIT_MAX_STRING_LEN',  'HPDF_LIMIT_MAX_XREF_ELEMENT',  'HPDF_LIMIT_MIN_INT',  'HPDF_LIMIT_MIN_REAL',  'HPDF_LINECAP_EOF',  'HPDF_LINEJOIN_EOF',  'HPDF_LineCap',  'HPDF_LineJoin',  'HPDF_LinkAnnot_SetBorderStyle',  'HPDF_LinkAnnot_SetHighlightMode',  'HPDF_LoadJpegImageFromFile',  'HPDF_LoadPngImageFromFile',  'HPDF_LoadPngImageFromFile2',  'HPDF_LoadRawImageFromFile',  'HPDF_LoadRawImageFromMem',  'HPDF_LoadTTFontFromFile',  'HPDF_LoadTTFontFromFile2',  'HPDF_LoadType1FontFromFile',  'HPDF_MAX_CHARSPACE',  'HPDF_MAX_DASH_PATTERN',  'HPDF_MAX_FONTSIZE',  'HPDF_MAX_GENERATION_NUM',  'HPDF_MAX_HORIZONTALSCALING',  'HPDF_MAX_JWW_NUM',  'HPDF_MAX_LEADING',  'HPDF_MAX_LINEWIDTH',  'HPDF_MAX_MAGNIFICATION_FACTOR',  'HPDF_MAX_PAGE_HEIGHT',  'HPDF_MAX_PAGE_SIZE',  'HPDF_MAX_PAGE_WIDTH',  'HPDF_MAX_WORDSPACE',  'HPDF_MAX_ZOOMSIZE',  'HPDF_MIN_CHARSPACE',  'HPDF_MIN_HORIZONTALSCALING',  'HPDF_MIN_MAGNIFICATION_FACTOR',  'HPDF_MIN_PAGE_HEIGHT',  'HPDF_MIN_PAGE_SIZE',  'HPDF_MIN_PAGE_WIDTH',  'HPDF_MIN_WORDSPACE',  'HPDF_MITER_JOIN',  'HPDF_NOERROR',  'HPDF_NOPNGLIB',  'HPDF_New',  'HPDF_NewDoc',  'HPDF_NewEx',  'HPDF_OBJ_ID_LEN',  'HPDF_OK',  'HPDF_Outline',  'HPDF_Outline_SetDestination',  'HPDF_Outline_SetOpened',  'HPDF_PAGE_LANDSCAPE',  'HPDF_PAGE_LAYOUT_EOF',  'HPDF_PAGE_LAYOUT_ONE_COLUMN',  'HPDF_PAGE_LAYOUT_SINGLE',  'HPDF_PAGE_LAYOUT_TWO_COLUMN_LEFT',  'HPDF_PAGE_LAYOUT_TWO_COLUMN_RIGHT',  'HPDF_PAGE_MODE_EOF',  'HPDF_PAGE_MODE_FULL_SCREEN',  'HPDF_PAGE_MODE_USE_ATTACHMENTS',  'HPDF_PAGE_MODE_USE_NONE',  'HPDF_PAGE_MODE_USE_OC',  'HPDF_PAGE_MODE_USE_OUTLINE',  'HPDF_PAGE_MODE_USE_THUMBS',  'HPDF_PAGE_NUM_STYLE_DECIMAL',  'HPDF_PAGE_NUM_STYLE_EOF',  'HPDF_PAGE_NUM_STYLE_LOWER_LETTERS',  'HPDF_PAGE_NUM_STYLE_LOWER_ROMAN',  'HPDF_PAGE_NUM_STYLE_UPPER_LETTERS',  'HPDF_PAGE_NUM_STYLE_UPPER_ROMAN',  'HPDF_PAGE_PORTRAIT',  'HPDF_PAGE_SIZE_A3',  'HPDF_PAGE_SIZE_A4',  'HPDF_PAGE_SIZE_A5',  'HPDF_PAGE_SIZE_B4',  'HPDF_PAGE_SIZE_B5',  'HPDF_PAGE_SIZE_COMM10',  'HPDF_PAGE_SIZE_EOF',  'HPDF_PAGE_SIZE_EXECUTIVE',  'HPDF_PAGE_SIZE_LEGAL',  'HPDF_PAGE_SIZE_LETTER',  'HPDF_PAGE_SIZE_US4x6',  'HPDF_PAGE_SIZE_US4x8',  'HPDF_PAGE_SIZE_US5x7',  'HPDF_PDFVer',  'HPDF_PROJECTING_SCUARE_END',  'HPDF_Page',  'HPDF_PageDirection',  'HPDF_PageLayout',  'HPDF_PageMode',  'HPDF_PageNumStyle',  'HPDF_PageSizes',  'HPDF_Page_Arc',  'HPDF_Page_BeginText',  'HPDF_Page_Circle',  'HPDF_Page_Clip',  'HPDF_Page_ClosePath',  'HPDF_Page_ClosePathEofillStroke',  'HPDF_Page_ClosePathFillStroke',  'HPDF_Page_ClosePathStroke',  'HPDF_Page_Concat',  'HPDF_Page_CreateDestination',  'HPDF_Page_CreateLinkAnnot',  'HPDF_Page_CreateTextAnnot',  'HPDF_Page_CreateURILinkAnnot',  'HPDF_Page_CurveTo',  'HPDF_Page_CurveTo2',  'HPDF_Page_CurveTo3',  'HPDF_Page_DrawImage',  'HPDF_Page_Ellipse',  'HPDF_Page_EndPath',  'HPDF_Page_EndText',  'HPDF_Page_Eoclip',  'HPDF_Page_Eofill',  'HPDF_Page_EofillStroke',  'HPDF_Page_ExecuteXObject',  'HPDF_Page_Fill',  'HPDF_Page_FillStroke',  'HPDF_Page_GRestore',  'HPDF_Page_GSave',  'HPDF_Page_GetCMYKFill',  'HPDF_Page_GetCMYKStroke',  'HPDF_Page_GetCharSpace',  'HPDF_Page_GetCurrentFont',  'HPDF_Page_GetCurrentFontSize',  'HPDF_Page_GetCurrentPos',  'HPDF_Page_GetCurrentPos2',  'HPDF_Page_GetCurrentTextPos',  'HPDF_Page_GetCurrentTextPos2',  'HPDF_Page_GetDash',  'HPDF_Page_GetFillingColorSpace',  'HPDF_Page_GetFlat',  'HPDF_Page_GetGMode',  'HPDF_Page_GetGStateDepth',  'HPDF_Page_GetGrayFill',  'HPDF_Page_GetGrayStroke',  'HPDF_Page_GetHeight',  'HPDF_Page_GetHorizontalScalling',  'HPDF_Page_GetLineCap',  'HPDF_Page_GetLineJoin',  'HPDF_Page_GetLineWidth',  'HPDF_Page_GetMiterLimit',  'HPDF_Page_GetRGBFill',  'HPDF_Page_GetRGBStroke',  'HPDF_Page_GetStrokingColorSpace',  'HPDF_Page_GetTextLeading',  'HPDF_Page_GetTextMatrix',  'HPDF_Page_GetTextRaise',  'HPDF_Page_GetTextRenderingMode',  'HPDF_Page_GetTextRise',  'HPDF_Page_GetTransMatrix',  'HPDF_Page_GetWidth',  'HPDF_Page_GetWordSpace',  'HPDF_Page_LineTo',  'HPDF_Page_MeasureText',  'HPDF_Page_MoveTextPos',  'HPDF_Page_MoveTextPos2',  'HPDF_Page_MoveTo',  'HPDF_Page_MoveToNextLine',  'HPDF_Page_Rectangle',  'HPDF_Page_SetCMYKFill',  'HPDF_Page_SetCMYKStroke',  'HPDF_Page_SetCharSpace',  'HPDF_Page_SetDash',  'HPDF_Page_SetExtGState',  'HPDF_Page_SetFlat',  'HPDF_Page_SetFontAndSize',  'HPDF_Page_SetGrayFill',  'HPDF_Page_SetGrayStroke',  'HPDF_Page_SetHeight',  'HPDF_Page_SetHorizontalScalling',  'HPDF_Page_SetLineCap',  'HPDF_Page_SetLineJoin',  'HPDF_Page_SetLineWidth',  'HPDF_Page_SetMiterLimit',  'HPDF_Page_SetRGBFill',  'HPDF_Page_SetRGBStroke',  'HPDF_Page_SetRotate',  'HPDF_Page_SetSize',  'HPDF_Page_SetSlideShow',  'HPDF_Page_SetTextLeading',  'HPDF_Page_SetTextMatrix',  'HPDF_Page_SetTextRaise',  'HPDF_Page_SetTextRenderingMode',  'HPDF_Page_SetTextRise',  'HPDF_Page_SetWidth',  'HPDF_Page_SetWordSpace',  'HPDF_Page_ShowText',  'HPDF_Page_ShowTextNextLine',  'HPDF_Page_ShowTextNextLineEx',  'HPDF_Page_Stroke',  'HPDF_Page_TextOut',  'HPDF_Page_TextRect',  'HPDF_Page_TextWidth',  'HPDF_Pages',  'HPDF_Point',  'HPDF_REAL',  'HPDF_REAL_LEN',  'HPDF_RENDERING_MODE_EOF',  'HPDF_RGBColor',  'HPDF_ROUND_END',  'HPDF_ROUND_JOIN',  'HPDF_ReadFromStream',  'HPDF_Rect',  'HPDF_ResetError',  'HPDF_ResetStream',  'HPDF_SHORT_BUF_SIZ',  'HPDF_STATUS',  'HPDF_STROKE',  'HPDF_STROKE_CLIPPING',  'HPDF_SaveToFile',  'HPDF_SaveToStream',  'HPDF_SetCompressionMode',  'HPDF_SetCurrentEncoder',  'HPDF_SetEncryptionMode',  'HPDF_SetErrorHandler',  'HPDF_SetInfoAttr',  'HPDF_SetInfoDateAttr',  'HPDF_SetOpenAction',  'HPDF_SetPageLayout',  'HPDF_SetPageMode',  'HPDF_SetPagesConfiguration',  'HPDF_SetPassword',  'HPDF_SetPermission',  'HPDF_SetViewerPreference',  'HPDF_Stream',  'HPDF_TALIGN_CENTER',  'HPDF_TALIGN_JUSTIFY',  'HPDF_TALIGN_LEFT',  'HPDF_TALIGN_RIGHT',  'HPDF_TEXT_DEFAULT_LEN',  'HPDF_TMP_BUF_SIZ',  'HPDF_TRUE',  'HPDF_TS_BARN_DOORS_HORIZONTAL_IN',  'HPDF_TS_BARN_DOORS_HORIZONTAL_OUT',  'HPDF_TS_BARN_DOORS_VERTICAL_IN',  'HPDF_TS_BARN_DOORS_VERTICAL_OUT',  'HPDF_TS_BLINDS_HORIZONTAL',  'HPDF_TS_BLINDS_VERTICAL',  'HPDF_TS_BOX_IN',  'HPDF_TS_BOX_OUT',  'HPDF_TS_DISSOLVE',  'HPDF_TS_EOF',  'HPDF_TS_GLITTER_DOWN',  'HPDF_TS_GLITTER_RIGHT',  'HPDF_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT',  'HPDF_TS_REPLACE',  'HPDF_TS_WIPE_DOWN',  'HPDF_TS_WIPE_LEFT',  'HPDF_TS_WIPE_RIGHT',  'HPDF_TS_WIPE_UP',  'HPDF_TextAlignment',  'HPDF_TextAnnot_SetIcon',  'HPDF_TextAnnot_SetOpened',  'HPDF_TextRenderingMode',  'HPDF_TextWidth',  'HPDF_TransMatrix',  'HPDF_TransitionStyle',  'HPDF_UINT',  'HPDF_UINT16',  'HPDF_UINT32',  'HPDF_UINT8',  'HPDF_UNICODE',  'HPDF_UNICODE_HEADER_LEN',  'HPDF_UseCNSEncodings',  'HPDF_UseCNSFonts',  'HPDF_UseCNTEncodings',  'HPDF_UseCNTFonts',  'HPDF_UseJPEncodings',  'HPDF_UseJPFonts',  'HPDF_UseKREncodings',  'HPDF_UseKRFonts',  'HPDF_VERSION_TEXT',  'HPDF_VER_12',  'HPDF_VER_13',  'HPDF_VER_14',  'HPDF_VER_15',  'HPDF_VER_16',  'HPDF_VER_EOF',  'HPDF_WMODE_EOF',  'HPDF_WMODE_HORIZONTAL',  'HPDF_WMODE_VERTICAL',  'HPDF_WritingMode',  'HPDF_XObject',  'HPDF_XYZ',

'NULL'
]