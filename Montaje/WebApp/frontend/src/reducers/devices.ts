import { createSlice, Dispatch, UnknownAction } from "@reduxjs/toolkit";
import { DeviceWithId } from "../types/device";
import { deleteOne, getAll } from "../services/devices";


const deviceSlice = createSlice({
    initialState: [] as DeviceWithId[],
    name: "devices",
    reducers: {
        set(_state, action) {
            return action.payload;
        },
        addOne(state, action) {
            return state.concat(action.payload);
        },
        removeOne(state, action) {
            return state.filter((e) => (e.id !== action.payload))
        }
    }
})

export const { set, addOne, removeOne } = deviceSlice.actions;

export const loadAllDevices = () => (
    async (dispatch: Dispatch) => {
        try {
            const data = await getAll();
            dispatch(set(data))
        } catch (error) {
            dispatch(set([]));
        }
    }
) as unknown as UnknownAction

export const removeDevice = (id: number) => (
    async (dispatch: Dispatch) => {
        try {
            await deleteOne(id)
            dispatch(removeOne(id))
        } catch (error) {
            alert("Ostia")
        }
    }
) as unknown as UnknownAction

const deviceReducer = deviceSlice.reducer
export default deviceReducer;