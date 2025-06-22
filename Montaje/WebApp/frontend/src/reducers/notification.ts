import { createSlice, Dispatch, UnknownAction } from "@reduxjs/toolkit";
import { Notification } from "../types/notification";


const notificationSlice = createSlice({
    initialState: {
        tailIndex: 0,
        headIndex: 0,
        notifications: {} as Record<number, Notification>,
    },
    name: "notification",
    reducers: {
        addNotification: (state, action) => {
            const { message, variant } = action.payload as Notification;
            let newNotification = { ...state.notifications };
            newNotification[state.tailIndex] = {
                message,
                variant,
            };
            return {
                headIndex: state.headIndex,
                tailIndex: state.tailIndex + 1,
                notifications: newNotification,
            }
        },
        removeNotification: (state) => {
            let newNotification = { ...state.notifications };
            delete newNotification[state.headIndex];
            if (state.headIndex >= state.tailIndex - 1) {
                return {
                    headIndex: 0,
                    tailIndex: 0,
                    notifications: {},
                }
            }
            return {
                headIndex: state.headIndex + 1,
                tailIndex: state.tailIndex,
                notifications: newNotification,
            }
        },
    }
});

export const { addNotification, removeNotification } = notificationSlice.actions;

export const newNotification = (notification: Notification) => (
    async (dispatch: Dispatch) => {
        dispatch(addNotification(notification));
        setTimeout(() => {
            dispatch(removeNotification());
        }, 5000);
    }
) as unknown as UnknownAction;

const notificationReducer = notificationSlice.reducer;
export default notificationReducer;