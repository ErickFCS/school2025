import { Notification } from "../types/notification";
import { Dispatch, UnknownAction, createSlice } from "@reduxjs/toolkit";


const notificationSlice = createSlice({
    initialState: {
        headIndex: 0,
        notifications: {} as Record<number, Notification>,
        tailIndex: 0
    },
    name: "notification",
    reducers: {
        addNotification: (state, action) => {
            const { message, variant } = action.payload as Notification;
            let newNotification = { ...state.notifications };
            newNotification[state.tailIndex] = {
                message,
                variant
            };
            return {
                headIndex: state.headIndex,
                notifications: newNotification,
                tailIndex: state.tailIndex + 1
            };
        },
        removeNotification: (state) => {
            let newNotification = { ...state.notifications };
            delete newNotification[state.headIndex];
            if (state.headIndex >= state.tailIndex - 1) {
                return {
                    headIndex: 0,
                    notifications: {},
                    tailIndex: 0
                };
            }
            return {
                headIndex: state.headIndex + 1,
                notifications: newNotification,
                tailIndex: state.tailIndex
            };
        }
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
