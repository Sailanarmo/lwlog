﻿#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename FlushPolicy, typename ThreadingPolicy>
	class file_sink 
		: public sink<uncolored_policy, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
	private:
		using sink_t = sink<uncolored_policy, ThreadingPolicy>;

	public:
		file_sink() = default;
		explicit file_sink(std::string_view path);

	public:
		void sink_it(const details::record& record) override;
	};

	template<typename FlushPolicy, typename ThreadingPolicy>
	file_sink<FlushPolicy, ThreadingPolicy>::file_sink(std::string_view path)
		: details::stream_writer<FlushPolicy>(path)
	{}

	template<typename FlushPolicy, typename ThreadingPolicy>
	void file_sink<FlushPolicy, ThreadingPolicy>::sink_it(const details::record& record)
	{
		sink_t::m_current_level = record.level;
		details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
	}
}