/**
 * @file editor_utils.hpp
 * @author Daniel Parker (DParker13)
 * @brief Shared editor utility helpers.
 * @version 0.1
 * @date 2026-04-15
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <SDL3/SDL_dialog.h>
#include <functional>
#include <string>

namespace HBE::Application::GUI {

    /**
     * @brief Generic SDL open-file-dialog callback.
     *
     * Invokes the callable stored in @p userdata with the selected path, then frees it.
     * Always call via ShowFileDialog so ownership is managed correctly.
     *
     * @param userdata Heap-allocated std::function<void(std::string_view)>*.
     * @param filelist Null-terminated list of selected file paths, or nullptr on error.
     * @param filter   Index of the active file filter (unused).
     */
    inline void SDLCALL OnFileDialogResult(void *userdata, const char *const *filelist, int filter) {
        (void)filter;
        auto *callback = static_cast<std::function<void(std::string_view)> *>(userdata);

        if (filelist == nullptr) {
            LOG(HBE::Core::LoggingType::ERROR, std::string("Failed to open file dialog: ") + SDL_GetError());
        }
        else if (*filelist == nullptr) {
            LOG(HBE::Core::LoggingType::INFO, "File selection canceled.");
        }
        else {
            LOG(HBE::Core::LoggingType::INFO, std::string("Selected file: ") + filelist[0]);
            (*callback)(filelist[0]);
        }

        delete callback;
    }

    /**
     * @brief Generic SDL open-file-dialog callback.
     *
     * Invokes the callable stored in @p userdata with the selected path, then frees it.
     * Always call via ShowFileDialog so ownership is managed correctly.
     *
     * @param userdata Heap-allocated std::function<void(std::string_view)>*.
     * @param filelist Null-terminated list of selected file paths, or nullptr on error.
     * @param filter   Index of the active file filter (unused).
     */
    inline void SDLCALL OnFolderDialogResult(void *userdata, const char *const *filelist, int filter) {
        (void)filter;
        auto *callback = static_cast<std::function<void(std::string_view)> *>(userdata);

        if (filelist == nullptr) {
            LOG(HBE::Core::LoggingType::ERROR, std::string("Failed to open file dialog: ") + SDL_GetError());
        }
        else if (*filelist == nullptr) {
            LOG(HBE::Core::LoggingType::INFO, "File selection canceled.");
        }
        else {
            LOG(HBE::Core::LoggingType::INFO, std::string("Selected file: ") + filelist[0]);
            (*callback)(filelist[0]);
        }

        delete callback;
    }

    /**
     * @brief Opens an SDL file dialog and invokes @p onSelected with the chosen path.
     *
     * @param window    Parent SDL window.
     * @param filters   Pointer to an array of SDL_DialogFileFilter (must outlive the dialog).
     * @param numFilters Number of entries in @p filters.
     * @param onSelected Callable invoked with the selected path on success.
     */
    inline void ShowFileDialog(SDL_Window *window, const SDL_DialogFileFilter *filters, int numFilters,
                               std::function<void(std::string_view)> onSelected) {
        auto *callback = new std::function<void(std::string_view)>(std::move(onSelected));
        SDL_ShowOpenFileDialog(OnFileDialogResult, callback, window, filters, numFilters, nullptr, false);
    }

    /**
     * @brief Opens an SDL file dialog and invokes @p onSelected with the chosen path.
     *
     * @param window    Parent SDL window.
     * @param onSelected Callable invoked with the selected path on success.
     */
    inline void ShowFolderDialog(SDL_Window *window, std::function<void(std::string_view)> onSelected) {
        auto *callback = new std::function<void(std::string_view)>(std::move(onSelected));
        SDL_ShowOpenFolderDialog(OnFileDialogResult, callback, window, nullptr, false);
    }

    /**
     * @brief Opens an SDL file dialog and invokes @p onSelected with the chosen path.
     *
     * @param window    Parent SDL window.
     * @param onSelected Callable invoked with the selected path on success.
     */
    inline void SaveFileDialog(SDL_Window *window, const SDL_DialogFileFilter *filters, int numFilters,
                               std::function<void(std::string_view)> onSelected) {
        auto *callback = new std::function<void(std::string_view)>(std::move(onSelected));
        SDL_ShowSaveFileDialog(OnFileDialogResult, callback, window, filters, numFilters, nullptr);
    }

} // namespace HBE::Application::GUI
