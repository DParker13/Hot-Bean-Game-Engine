/**
 * @file console_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the console window for the editor GUI.
 * Displays debug output and application messages.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#include "console_window.hpp"
#include <HotBeanEngine/application/application.hpp>
#include <imgui_internal.h>

namespace HBE::GUI {
    using namespace Core;

    ConsoleWindow::ConsoleWindow() : IWindow("Console") {
        m_logging_level_filter = LOGGING_LEVEL; // Set the initial logging level filter to the global logging level
    }

    void ConsoleWindow::RenderWindow() {
        if (ImGui::Begin(m_name.c_str(), &m_open)) {
            // Auto-scroll toggle button
            if (ImGui::Button(m_auto_scroll ? "Auto-Scroll: ON" : "Auto-Scroll: OFF")) {
                m_auto_scroll = !m_auto_scroll;
            }

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            if (ImGui::Button("Clear Console")) {
                m_log_buffer.clear();
            }

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            if (ImGui::Button("Copy to Clipboard")) {
                std::string allLogs;
                for (const auto &[level, logEntry] : m_log_buffer) {
                    allLogs += logEntry + "\n";
                }
                ImGui::SetClipboardText(allLogs.c_str());
            }

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            // Logging level filter dropdown
            ImGui::Text("Min Level:");
            ImGui::SameLine();
            const char *logLevelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
            int currentLevel = static_cast<int>(m_logging_level_filter);
            ImGui::SetNextItemWidth(ImGui::CalcTextSize("WARNING").x + ImGui::GetStyle().FramePadding.x * 8);
            if (ImGui::Combo("##LoggingLevel", &currentLevel, logLevelNames, IM_ARRAYSIZE(logLevelNames))) {
                m_logging_level_filter = static_cast<LoggingType>(currentLevel);
            }

            ImGui::Separator();

            if (!m_log_buffer.empty()) {
                if (ImGui::BeginChild("LogScrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
                    for (const auto &[level, logEntry] : m_log_buffer) {
                        // Only display logs that meet the minimum level threshold
                        if (level >= m_logging_level_filter) {
                            ImGui::TextWrapped("%s", logEntry.c_str());
                        }
                    }

                    // Scroll to bottom if new log was added and auto-scroll is enabled
                    if (m_should_scroll_to_bottom && m_auto_scroll) {
                        ImGui::SetScrollHereY(1.0f);
                        m_should_scroll_to_bottom = false;
                    }
                }
                ImGui::EndChild();
            }
        }
        ImGui::End();
    }

    void ConsoleWindow::OnLog(LoggingType level, std::string_view message) {
        m_log_buffer.push_back({level, std::string(message)});
        m_should_scroll_to_bottom = true;

        // If buffer exceeds max size, remove the oldest entry
        if (m_log_buffer.size() > m_max_log_buffer_size) {
            m_log_buffer.pop_front();
        }
    }
} // namespace HBE::GUI