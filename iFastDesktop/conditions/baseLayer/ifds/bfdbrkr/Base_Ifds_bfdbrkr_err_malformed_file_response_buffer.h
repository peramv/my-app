#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdbrkr_err_malformed_file_response_buffer : public CConditionObject
	{
	public:
		CBase_Ifds_bfdbrkr_err_malformed_file_response_buffer() { }
		~CBase_Ifds_bfdbrkr_err_malformed_file_response_buffer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MALFORMED_FILE_RESPONSE_BUFFER")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("File Response Buffer is malformed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("File Response Buffer is malformed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tampon de réponse du fichier est incorrect.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("File Response Buffer is malformed.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



