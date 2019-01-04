#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_malformed_stub_file_response_buffer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_malformed_stub_file_response_buffer() { }
		~CIFast_IFast_ifastdbrkr_err_malformed_stub_file_response_buffer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MALFORMED_STUB_FILE_RESPONSE_BUFFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stub File Response Buffer is malformed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mémoire tampon de réponse du fichier source est malformée.")); }

        // Actions
	};
}



