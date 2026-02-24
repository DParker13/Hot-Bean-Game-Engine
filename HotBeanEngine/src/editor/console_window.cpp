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
#include <imgui_internal.h>

namespace HBE::Application::GUI {
    ConsoleWindow::ConsoleWindow() : IWindow("Console") {}

    void ConsoleWindow::RenderWindow() {
        if (ImGui::Begin(m_name.c_str(), &m_open)) {
            // Auto-scroll toggle button
            if (ImGui::Button(m_autoScroll ? "Auto-Scroll: ON" : "Auto-Scroll: OFF")) {
                m_autoScroll = !m_autoScroll;
            }

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            if (ImGui::Button("Clear Console")) {
                m_logBuffer.clear();
            }

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            if (ImGui::Button("Copy to Clipboard")) {
                std::string allLogs;
                for (const auto &[level, logEntry] : m_logBuffer) {
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
            int currentLevel = static_cast<int>(m_loggingLevelFilter);
            ImGui::SetNextItemWidth(ImGui::CalcTextSize("WARNING").x + ImGui::GetStyle().FramePadding.x * 8);
            if (ImGui::Combo("##LoggingLevel", &currentLevel, logLevelNames, IM_ARRAYSIZE(logLevelNames))) {
                m_loggingLevelFilter = static_cast<HBE::Core::LoggingType>(currentLevel);
            }

            ImGui::Separator();

            if (!m_logBuffer.empty()) {
                if (ImGui::BeginChild("LogScrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
                    for (const auto &[level, logEntry] : m_logBuffer) {
                        // Only display logs that meet the minimum level threshold
                        if (level >= m_loggingLevelFilter) {
                            ImGui::TextWrapped("%s", logEntry.c_str());
                        }
                    }

                    // Scroll to bottom if new log was added and auto-scroll is enabled
                    if (m_shouldScrollToBottom && m_autoScroll) {
                        ImGui::SetScrollHereY(1.0f);
                        m_shouldScrollToBottom = false;
                    }

                    ImGui::EndChild();
                }
            }
        }
        ImGui::End();
    }

    void ConsoleWindow::OnLog(HBE::Core::LoggingType level, std::string_view message) {
        m_logBuffer.push_back({level, std::string(message)});
        m_shouldScrollToBottom = true;

        // If buffer exceeds max size, remove the oldest entry
        if (m_logBuffer.size() > m_maxLogBufferSize) {
            m_logBuffer.pop_front();
        }
    }
} // namespace HBE::Application::GUI