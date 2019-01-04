#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_diawd23_diawd23_container_already_open : public CConditionObject
	{
	public:
		CIFast_Infrastructure_diawd23_diawd23_container_already_open() { }
		~CIFast_Infrastructure_diawd23_diawd23_container_already_open() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_CONTAINER_ALREADY_OPEN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD Container already open.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD Container already open.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der AWD-Container ist bereits geöffnet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El contenedor de AWD ya está abierto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conteneur AWD est déjà ouvert.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-container is al geopend")); }

        // Actions
	};
}



