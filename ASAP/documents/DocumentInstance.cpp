#include "DocumentInstance.h"

#include <sstream>

namespace ASAP
{
	DocumentInstance::DocumentInstance(Document& document, const uint16_t instance_id)
		: document(&document), name(GetInstanceName_(document, instance_id))
	{
		SetupInstance_();
	}

	DocumentInstance::DocumentInstance(std::shared_ptr<Document> document, const uint16_t instance_id)
		: document(document), name(GetInstanceName_(*document, instance_id))
	{
		SetupInstance_();
	}

	DocumentInstance::DocumentInstance(std::weak_ptr<Document> document, const uint16_t instance_id)
		: document(document), name(GetInstanceName_(*this->document, instance_id))
	{
		SetupInstance_();
	}

	std::string DocumentInstance::GetInstanceName_(Document& document, const uint16_t instance_id)
	{
		std::stringstream instance_name;
		instance_name << document.GetFilepath().filename().string() << " (" << std::to_string(instance_id) << ")";
		return instance_name.str();
	}

	void DocumentInstance::SetupInstance_(void)
	{
		const TileInformation& tile_info(this->document->GetTileInformation());
		this->current_level = tile_info.top_level;
		this->minimap_coverage.resize(tile_info.top_level + 1);
	}
}