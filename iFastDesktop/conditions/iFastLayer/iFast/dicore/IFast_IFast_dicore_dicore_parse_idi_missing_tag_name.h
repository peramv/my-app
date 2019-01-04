#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_parse_idi_missing_tag_name : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_parse_idi_missing_tag_name() { }
		~CIFast_IFast_dicore_dicore_parse_idi_missing_tag_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PARSE_IDI_MISSING_TAG_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The server cannot determine the service required")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The server cannot determine the service required")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Server kann den notwendigen Service nicht bestimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El servidor no puede determinar el servicio requerido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le serveur ne peut déterminer le service requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De server kan de gewenste sessie niet vaststellen")); }

        // Actions
	};
}



