#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_invalid_group_code : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_invalid_group_code() { }
		~CIFast_Infrastructure_ifastdbrkr_err_invalid_group_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GROUP_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD work was successfully created.  %WorkObjectDetails%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD work was successfully created.  %WorkObjectDetails%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Erstellung der AWD-Arbeit war erfolgreich.  %WorkObjectDetails%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tarea de AWD se creó con éxito.  %WorkObjectDetails%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le travail AWD a été créé avec succès. %WorkObjectDetails%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-werk is gemaakt.  %WorkObjectDetails%")); }

        // Actions
	};
}



