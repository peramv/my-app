#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastawd_err_no_awd_source_image : public CConditionObject
	{
	public:
		CIFast_IFast_ifastawd_err_no_awd_source_image() { }
		~CIFast_IFast_ifastawd_err_no_awd_source_image() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_AWD_SOURCE_IMAGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastawd")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no AWD source image available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("There is no AWD source image available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune image de source AWD n'est disponible.")); }

        // Actions
	};
}



